#include "ACR122CardHandler.h"
#include <qDebug>
#include <QSharedPointer>
#include "tools/StringTools.h"

ACR122CardHandler::ACR122CardHandler(QObject *parent) : RFIDComponent(parent)
{
    connectTimer = new QTimer(this);

    connect(this, SIGNAL(userWriteSuccess()), this, SLOT(onUserWriteSuccess()));
    connect(this, SIGNAL(cardReaderError(CardReaderError)), this, SLOT(onCardReaderError(CardReaderError)));
    connect(this, SIGNAL(userIdReadSuccess(const QString&)), this, SLOT(onUserIdReadSuccess(const QString&)));
    connect(this, SIGNAL(userDataReadSuccess(const QString&)), this, SLOT(onUserDataReadSuccess(const QString&)));

    fillBlockAdresses();
}

ACR122CardHandler::~ACR122CardHandler()
{
    disconnect(this, SIGNAL(userWriteSuccess()), this, SLOT(onUserWriteSuccess()));
    disconnect(this, SIGNAL(cardReaderError(CardReaderError)), this, SLOT(onCardReaderError(CardReaderError)));
    disconnect(this, SIGNAL(userIdReadSuccess(const QString&)), this, SLOT(onUserIdReadSuccess(const QString&)));
    disconnect(this, SIGNAL(userDataReadSuccess(const QString&)), this, SLOT(onUserDataReadSuccess(const QString&)));

    if(connectTimer)
    {
        disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
        disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
        delete connectTimer;
    }
}

void ACR122CardHandler::setConfig(ConfigPtr config)
{
    RFIDComponent::setConfig(config);
    writeValidation = validationFromString(_rfidConfig.writeValidation);
}

ACR122CardHandler::WriteValidation ACR122CardHandler::validationFromString(const QString& value)
{
    if(value == "idOnly")
    {
        return WriteValidation::IdOnly;
    }
    else if(value == "allData")
    {
        return WriteValidation::AllData;
    }

    return WriteValidation::None;
}

void ACR122CardHandler::startReading()
{
    setCardReaderState(CardReaderState::Reading);
    timerRestart();
    connect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
}

void ACR122CardHandler::startReadingId()
{
    readIdOnly = true;
    startReading();
}

void ACR122CardHandler::startReadingAllData()
{
    readIdOnly = false;
    startReading();
}

void ACR122CardHandler::startWriting(const QString& data)
{
    setCardReaderState(CardReaderState::Writing);
    lastUserData = data;
    // timerRestart();
    // connect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    onWritingUpdate();
}

void ACR122CardHandler::startWriting(int id,
                                     const QString& name,
                                     const QString& surname,
                                     const QString& phone,
                                     const QString& email,
                                     const QString& gender)
{
    if(formatUserData(id, name, surname, phone, email, gender))
    {
        startWriting(lastUserData);
    }
}

bool ACR122CardHandler::formatUserData(int id,
                                       const QString& name,
                                       const QString& surname,
                                       const QString& phone,
                                       const QString& email,
                                       const QString& gender)
{
    // block 0x01: {678}0000000...
    // block 0x02 -... {name,surname,phone,email}

    QString formattedPhone = phone;

    if(!StringTools::convertPhoneNumber(formattedPhone))
    {
        qDebug()<<"I can Format phone !!!!! ";
        emit cardReaderError(CardReaderError::DataFormatError);
        return false;
    }

    qDebug()<<"Formated phone "<<formattedPhone;

    blockZeroDataInit();
    lastUserId = QString::number(id);
    QString userId = BRACKET_1 + lastUserId + BRACKET_2;
    userId = blockZeroData.replace(0, userId.size(), userId);

    lastUserData = userId
            + BRACKET_1 +
            name + DELIM +
            surname + DELIM +
            formattedPhone + DELIM +
            email + DELIM +
            gender + BRACKET_2;

    return true;
}

void ACR122CardHandler::timerRestart()
{
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
    connectTimer->start(checkMills);
}

void ACR122CardHandler::stopAll()
{
    setCardReaderState(CardReaderState::Stopped);
    connectTimer->stop();
}

bool ACR122CardHandler::cardPreparedSuccess()
{
    bool cardPrepared = true;

    if(!establishContext())
    {
        qDebug()<<"cant establish context";
        emit cardReaderError(CardReaderError::NoCardReader);
        cardPrepared = false;
    }

    else if(!checkIsDeviceConnected())
    {
        qDebug()<<"cant device connected";
        emit cardReaderError(CardReaderError::NoCardReader);
        cardPrepared = false;
    }

    else if(!cardConnect())
    {
        emit cardReaderError(CardReaderError::NoCard);
        cardPrepared = false;
    }
    else if(!loadKey())
    {
        emit cardReaderError(CardReaderError::LoadKeyError);
        cardPrepared = false;
    }

    if(!cardPrepared)
    {
        releaseCardReader();
    }

    return cardPrepared;
}

void ACR122CardHandler::releaseCardReader()
{
    SCardDisconnect(card_handle_, SCARD_UNPOWER_CARD);
    SCardReleaseContext(card_context_);
}

void ACR122CardHandler::onWritingUpdate()
{
    if(!cardPreparedSuccess())
    {
        return;
    }

    if(!startCommandsInit)
    {
        runStartCommands();
    }

    connectTimer->stop();

    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantStartTransaction);
        return;
    }

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    QByteArray cardData = lastUserData.toUtf8();
    int blocksNeeded = getBlocksNeedForWriting(cardData);
    qDebug()<<"before align: "<<cardData;
    alignData(cardData);

    lastUserData = cardData;
    qDebug()<<"fullCardData: "<<lastUserData;
    qDebug()<<"write bytes: "<<cardData.size();
    qDebug()<<"blocksNeeded: "<<blocksNeeded;
    int blockOffset = 0;

    const int MAX_BLOCK_FOR_WRITE = blockAdresses.size();

    if(blocksNeeded > MAX_BLOCK_FOR_WRITE)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::WriteError);
        return;
    }

    for(int i = 0; i < blocksNeeded; i++)
    {
        blockAdress = blockAdresses[i];

        if(!blockAuthenticate(blockAdress))
        {
            releaseCardReader();
            emit cardReaderError(CardReaderError::AuthError);
            return;
        }

        QByteArray blockData;
        for(int i = 0; i < ONE_BLOCK_SIZE; i++)
        {
            blockData[i] = cardData[blockOffset + i];
        }
        blockOffset += ONE_BLOCK_SIZE;

        qDebug()<<"write to block: "<<blockAdress<<" : "<<blockData;

        if(!writeBlockData(blockAdress, blockData))
        {
            releaseCardReader();
            emit cardReaderError(CardReaderError::WriteError);
            return;
        }
    }

    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantEndTransaction);
        return;
    }

    emit userWriteSuccess();
}

void ACR122CardHandler::onUserWriteSuccess()
{
    if(writeValidation == WriteValidation::None)
    {
        releaseCardReader();
        emit validationSuccess();
    }
    else if(writeValidation == WriteValidation::IdOnly)
    {
        setCardReaderState(CardReaderState::Validating);
        readId();
    }
    else if(writeValidation == WriteValidation::AllData)
    {
        setCardReaderState(CardReaderState::Validating);
        readAllData();
    }
}

void ACR122CardHandler::onReadingUpdate()
{
    readIdOnly ? readId() : readAllData();
}

void ACR122CardHandler::readId()
{
    if(!cardPreparedSuccess())
    {
        return;
    }

    if(!startCommandsInit)
    {
        runStartCommands();
    }

    connectTimer->stop();

    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantStartTransaction);
        return;
    }

    QByteArray data = "";
    blockAdress = blockAdresses[0];

    if(!blockAuthenticate(blockAdress))
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::AuthError);
        return;
    }

    if(!readBlockData(blockAdress, data))
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::ReadError);
        return;
    }

    QString id = QString(data);
    int startIndex = id.indexOf(BRACKET_1);
    int endIndex = id.indexOf(BRACKET_2);
    if(startIndex != -1 && endIndex != -1)
    {
        id = id.mid(startIndex + 1, endIndex - 1);
        emit userIdReadSuccess(id);
    }
    else
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CardParsing);
        return;
    }

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantEndTransaction);
        return;
    }

    releaseCardReader();
}

void ACR122CardHandler::readAllData()
{
    if(!cardPreparedSuccess())
    {
        return;
    }

    if(!startCommandsInit)
    {
        runStartCommands();
    }

    connectTimer->stop();

    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantStartTransaction);
        return;
    }

    QByteArray data = "";
    QByteArray fulldata;
    int lastSymbolCount = 0;
    const int lastSymbols = 2;

    for(int i = 0; i < blockAdresses.size(); i++)
    {
        blockAdress = blockAdresses[i];

        if(!blockAuthenticate(blockAdress))
        {
            releaseCardReader();
            emit cardReaderError(CardReaderError::AuthError);
            return;
        }

        if(!readBlockData(blockAdress, data))
        {
            releaseCardReader();
            emit cardReaderError(CardReaderError::ReadError);
            return;
        }

        fulldata.append(data);

        int lastSymbol = data.indexOf(BRACKET_2);
        if(lastSymbol != -1)
        {
            lastSymbolCount++;
            if(lastSymbolCount == lastSymbols)
            {
                break;
            }
        }
    }
    qDebug()<<"fulldata "<<QString(fulldata);
    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        releaseCardReader();
        emit cardReaderError(CardReaderError::CantEndTransaction);
        return;
    }

    releaseCardReader();

    if(lastSymbolCount == lastSymbols)
    {
        emit userDataReadSuccess(QString(fulldata));
    }
    else
    {
        emit cardReaderError(CardReaderError::CardParsing);
    }
}

void ACR122CardHandler::onUserDataReadSuccess(const QString& data)
{
    startValidation(data);
}

void ACR122CardHandler::onUserIdReadSuccess(const QString& data)
{
    startValidation(data);
}

void ACR122CardHandler::startValidation(const QString& data)
{
    if(cardReaderState == CardReaderState::Validating)
    {
        if(writeValidation == WriteValidation::IdOnly)
        {
            if(data == lastUserId)
            {
                emit validationSuccess();
            }
            else
            {
                emit validationFailed();
            }
        }
        else if(writeValidation == WriteValidation::AllData)
        {
            qDebug()<< "Validated "<<data<<lastUserData;

            if(compareAllData(data, lastUserData))
            {
                qDebug()<<"Validated success";
                emit validationSuccess();
            }
            else
            {
                qDebug()<<"VAlidated  failed";
                emit validationFailed();
            }
        }
    }

    setCardReaderState(CardReaderState::Stopped);
}

bool ACR122CardHandler::compareAllData(const QString& data1, const QString& data2)
{
    return data1 == data2;
}

void ACR122CardHandler::onCardReaderError(CardReaderError error)
{
    setCardReaderState(CardReaderState::Stopped);
}

void ACR122CardHandler::resetReadingState()
{
    startReading();
}

bool ACR122CardHandler::establishContext()
{
    return SCardEstablishContext(SCARD_SCOPE_USER, 0, 0, &card_context_) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::cardConnect()
{
    DWORD dwAP = 0;
    LPCWSTR cardReaderName = reinterpret_cast<LPCWSTR>(rfidConfig().type.unicode());
    return SCardConnect(card_context_, cardReaderName, SCARD_SHARE_SHARED, SCARD_PROTOCOL_Tx, &card_handle_, &dwAP) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::checkIsDeviceConnected()
{
    LPWSTR mszReaders;
    DWORD dwReaders = SCARD_AUTOALLOCATE;

    if(SCardListReadersW(card_context_, NULL, (LPWSTR)&mszReaders, &dwReaders) != SCARD_S_SUCCESS)
    {
        return false;
    }

    QByteArray buffer;
    wchar_t *it = mszReaders;

    while(*it !='\0')
    {
        buffer.append(QChar(*it));
        *it++;
    }
    QString cardReaderName(buffer);

    if(SCardFreeMemory(card_context_, mszReaders)!= SCARD_S_SUCCESS)
    {
        return false;
    }

    return cardReaderName.contains(rfidConfig().type);
}

bool ACR122CardHandler::loadKey()
{
    uint8_t bytes[11] = {0xff, 0x82, 0x00, keyLocation, 0x06/* key length */, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    return SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::blockAuthenticate(uint8_t blockNumber)
{
    uint8_t bytes[10] = {0xff, 0x86, 0x00, 0x00, 0x05, 0x01, 0x00, blockNumber, keyType, keyLocation};
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    return SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::readBlockData(uint8_t blockNumber, QByteArray& data)
{
    uint8_t bytesNum = 0x010;
    QString str = QString::number(bytesNum);
    qDebug()<<"-------------------------------";
    qDebug()<<"read blockNumber :" <<blockNumber;
    qDebug()<<"read bytes :" << str.toInt();

    uint8_t bytes[5] = {0xff, 0xB0, 0x00, blockNumber, bytesNum};
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];


    qDebug()<<"try to read";
    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
    {
        qDebug()<<"cant read";
        return false;
    }

    qDebug()<<"readed"<<cbRecv;

    if(cbRecv < 2)
    {
        return false;
    }

    QByteArray recieve;
    for (int i = 0; i < cbRecv - 2; i++)
    {
        recieve.append(pbRecv[i]);
    }

    qDebug()<<"bytes :" << data;
    data = recieve;
    return true;
}

bool ACR122CardHandler::writeBlockData(uint8_t blockNumber, const QByteArray& data)
{
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    const int reserveBytes = 5;
    const int size = reserveBytes + 16;
    uint8_t bytes[size];

    bytes[0] = 0xff;
    bytes[1] = 0xD6;
    bytes[2] = 0x00;
    bytes[3] = blockNumber;
    bytes[4] = 0x10;

    for(int i = reserveBytes; i < size; i++)
    {
        bytes[i] = data[i - reserveBytes];
    }

    return SCardTransmit(card_handle_, protocol, bytes,  sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

void ACR122CardHandler::runStartCommands()
{
    startCommandsInit = true;
    beepCommand(rfidConfig().beepEnabled);
}

bool ACR122CardHandler::beepCommandDirect(bool enabled)
{
    if(!cardPreparedSuccess())
    {
        return false;
    }
    beepCommand(enabled);
}

bool ACR122CardHandler::beepCommand(bool enabled)
{
    BYTE pbRecv[MAX_APDU_SIZE];
    DWORD cbRecv = MAX_APDU_SIZE;
    uint8_t bytes[5] = {0xff, 0x00, 0x52, enabled ? 0xff: 0x00, 0x00};
    return SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::getStatusCommand()
{
    if(!cardPreparedSuccess())
    {
        return false;
    }

    BYTE pbRecv[MAX_APDU_SIZE];
    DWORD cbRecv = MAX_APDU_SIZE;
    uint8_t bytes[7] = {0xff, 0x00, 0x00, 0x00, 0x02, 0xD4, 0x04};

    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
    {
        return false;
    }

    if(cbRecv < 2)
    {
        return false;
    }

    QByteArray recieve;
    for (int i = 0; i < cbRecv - 2; i++)
    {
        recieve.append(pbRecv[i]);
    }

    qDebug()<<"bytes status :" << recieve;

    return true;
}


void ACR122CardHandler::fillBlockAdresses()
{
    //fill adress array with 64 blocks start adresses
    //every third block - trail block, does'n use
    //read milfare specs

    int k = 0;
    int allBlocksNum = 64;
    int hexBase = 16;

    for(int i = 0; i< allBlocksNum; i++)
    {
        if(k++ == 3)
        {
            k = 0;
        }
        else
        {
            QString hex = QString::number(i, hexBase);
            bool ok;
            const unsigned int parsedValue = hex.toUInt(&ok, hexBase);
            blockAdresses.push_back(parsedValue);
        }
    }
    blockAdresses.pop_front();//don't use 0x00 block
    blockAdress = blockAdresses[0];

    blockZeroDataInit();
}

void ACR122CardHandler::blockZeroDataInit()
{
    blockZeroData.clear();
    blockZeroData.fill('0', ONE_BLOCK_SIZE);
}

int ACR122CardHandler::getBlocksNeedForWriting(const QByteArray& cardData)
{
    int addBlock = cardData.size() % ONE_BLOCK_SIZE != 0 ? 1 : 0;
    return cardData.size() / ONE_BLOCK_SIZE + addBlock;
}

void ACR122CardHandler::alignData(QByteArray& cardData)
{
    int remainder = cardData.size() % ONE_BLOCK_SIZE;
    if(remainder !=0 )
    {
        for(int i = 0; i < ONE_BLOCK_SIZE - remainder; i++)
        {
            cardData.append('0');
        }
    }
}

//void ACR122CardHandler::resetCard()
//{
//    establishContext();
//    cardConnect();

//    uint8_t bytes[21] = {0xFF, 0xD6, 0x00, 0x03, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF};

//    DWORD cbRecv = MAX_APDU_SIZE;
//    BYTE pbRecv[MAX_APDU_SIZE];
//    if(SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS)
//    {
//        qDebug()<<"success";
//    }
//    else
//    {
//        qDebug()<<"FAILLLLL";
//    }
//}

//bool ACR122CardHandler::cardStatus()
//{
//    printf("SCardStatus : ");
//       dwReaderLen = MAX_READER_NAME_SIZE;
//       pcReaders = (LPWSTR)malloc(sizeof(char) * MAX_READER_NAME_SIZE);

//       rv = SCardStatus(hCard, pcReaders, &dwReaderLen, &dwState,
//           &dwProt, pbAtr, &dwAtrLen);
//}

//bool ACR122CardHandler::getFirmVer(QString& ver)
//{
//    DWORD cbRecv = MAX_APDU_SIZE;
//    BYTE pbRecv[MAX_APDU_SIZE];
//    uint8_t bytes[5] = {0xff, 0x00, 0x48, 0x00, 0x00};

//    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
//    {
//        return false;
//    }

//    ver = "";
//    for (int i = 0; i < cbRecv - 2; i++)
//    {
//        ver += QString("%02").arg(pbRecv[i]);
//    }

//    return true;
//}

//bool ACR122CardHandler::getCardUid(QString& uid)
//{
//    DWORD cbRecv = MAX_APDU_SIZE;
//    BYTE pbRecv[MAX_APDU_SIZE];
//    uint8_t bytes[5] = {0xff, 0xCA, 0x00, 0x00, 0x00};

//    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
//    {
//        return false;
//    }

//    uid = "";
//    for (int i = 0; i < cbRecv - 2; i++)
//    {
//        uid += QString("%02").arg(pbRecv[i]);
//    }

//    return true;
//}

//void ACR122CardHandler::getCardAttributes()
//{
//    if(!establishContext())
//    {
//        emit cardReaderError(CardReaderError::NoCardReader);
//        return;
//    }

//    if(!checkIsDeviceConnected())
//    {
//        emit cardReaderError(CardReaderError::NoCardReader);
//        return;
//    }

//    if(!cardConnect())
//    {
//        emit cardReaderError(CardReaderError::NoCard);
//        return;
//    }

//    LPBYTE   pbAttr = NULL;
//    DWORD    cByte = SCARD_AUTOALLOCATE;
//    DWORD    i;
//    LONG	 lRetValue;

//    // Gets the current reader attributes for the given handle.
//    if( SCardGetAttrib(
//                card_context_,  // Card handle.
//                SCARD_ATTR_VENDOR_NAME, // Attribute identifier.
//                (LPBYTE)&pbAttr,    // Attribute buffer.
//                &cByte)== SCARD_S_SUCCESS)

//    {
//        qDebug()<<"AttrSuccess";
//    }
//    else
//    {
//        qDebug()<<"Attr failed";
//    }
//}
