#include "ACR122CardHandler.h"
#include <qDebug>
#include <QSharedPointer>
#define MAX_APDU_SIZE 255

ACR122CardHandler::ACR122CardHandler(QObject *parent) : RFIDComponent(parent)
{
    connectTimer = new QTimer(this);
    fillBlockAdresses();

    connect(this, SIGNAL(userWriteSuccess()), this, SLOT(onUserWriteSuccess()));
    connect(this, SIGNAL(cardReaderError(CardReaderError)), this, SLOT(onCardReaderError(CardReaderError)));
    connect(this, SIGNAL(userReadSuccess(const QString&)), this, SLOT(onUserReadSuccess(const QString&)));
}

ACR122CardHandler::~ACR122CardHandler()
{
    disconnect(this, SIGNAL(userWriteSuccess()), this, SLOT(onUserWriteSuccess()));
    disconnect(this, SIGNAL(cardReaderError(CardReaderError)), this, SLOT(onCardReaderError(CardReaderError)));
    disconnect(this, SIGNAL(userReadSuccess(const QString&)), this, SLOT(onUserReadSuccess(const QString&)));
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
}

void ACR122CardHandler::setConfig(ConfigPtr config)
{
    RFIDComponent::setConfig(config);
    writeValidation = WriteValidation::None;

    if(_rfidConfig.writeValidation == "idOnly")
    {
        writeValidation = WriteValidation::IdOnly;
    }
    else if(_rfidConfig.writeValidation == "allData")
    {
        writeValidation = WriteValidation::AllData;
    }
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
    timerRestart();
    connect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
}

void ACR122CardHandler::startWriting(int id, const QString& name, const QString& surname, const QString& phone, const QString& email)
{
    setCardReaderState(CardReaderState::Writing);

    lastUserId = QString::number(id);
    blockZeroDataInit();
    QString userId = BRACKET_1 + lastUserId + BRACKET_2;
    userId = blockZeroData.replace(0, userId.size(), userId);
    lastUserData = userId + BRACKET_1 + name + DELIM + surname + DELIM + phone + DELIM + email + BRACKET_2;

    startWriting(lastUserData);
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
        emit cardReaderError(CardReaderError::NoCardReader);
        cardPrepared = false;
    }
    
    else if(!checkIsDeviceConnected())
    {
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
    //  LPCWSTR cardReaderName = reinterpret_cast<LPCWSTR>(rfidConfig().type.unicode());
    //  SCardFreeMemory(card_context_, cardReaderName);
    // SCardDisconnect(card_handle_, SCARD_LEAVE_CARD);
    SCardReleaseContext(card_context_);
}

void ACR122CardHandler::onWritingUpdate()
{
    connectTimer->stop();
    
    if(!cardPreparedSuccess())
    {
        return;
    }
    
    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantStartTransaction);
        releaseCardReader();
        return;
    }

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    QByteArray cardData = lastUserData.toUtf8();
    int blocksNeeded = getBlocksNeedForWriting(cardData);
    alignData(cardData);
    qDebug()<<"fullCardData: "<<lastUserData;
    qDebug()<<"write bytes: "<<cardData.size();
    qDebug()<<"blocksNeeded: "<<blocksNeeded;
    int blockOffset = 0;

    for(int i = 0; i < blocksNeeded; i++)
    {
        blockAdress = blockAdresses[i];
        
        if(!blockAuthenticate(blockAdress))
        {
            emit cardReaderError(CardReaderError::AuthError);
            releaseCardReader();
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
            emit cardReaderError(CardReaderError::WriteError);
            releaseCardReader();
            return;
        }
    }
    
    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantEndTransaction);
        releaseCardReader();
        return;
    }
    
    releaseCardReader();
    emit userWriteSuccess();
    connectTimer->stop();
}

void ACR122CardHandler::onUserWriteSuccess()
{
    if(writeValidation == WriteValidation::None)
    {
        emit validationSuccess();
        return;
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

void ACR122CardHandler::onUserReadSuccess(const QString& data)
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
            if(data == lastUserData)
            {
                emit validationSuccess();
            }
            else
            {
                emit validationFailed();
            }
        }
    }

    setCardReaderState(CardReaderState::Stopped);
}

void ACR122CardHandler::onCardReaderError(CardReaderError error)
{

    setCardReaderState(CardReaderState::Stopped);
}

void ACR122CardHandler::onReadingUpdate()
{
    connectTimer->stop();
    readIdOnly ? readId() : readAllData();
}

void ACR122CardHandler::readId()
{
    if(!cardPreparedSuccess())
    {
        return;
    }

    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantStartTransaction);
        releaseCardReader();
        return;
    }

    QByteArray data = "";
    blockAdress = blockAdresses[0];

    if(!blockAuthenticate(blockAdress))
    {
        emit cardReaderError(CardReaderError::AuthError);
        releaseCardReader();
        return;
    }

    if(!readBlockData(blockAdress, data))
    {
        emit cardReaderError(CardReaderError::ReadError);
        releaseCardReader();
        return;
    }

    QString id = QString(data);
    int startIndex = id.indexOf(BRACKET_1);
    int endIndex = id.indexOf(BRACKET_2);
    if(startIndex != -1 && endIndex != -1)
    {
        id = id.mid(startIndex + 1, endIndex-1);
        emit userReadSuccess(id);
    }
    else
    {
        emit cardReaderError(CardReaderError::ReadError);
        releaseCardReader();
        return;
    }

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantEndTransaction);
        releaseCardReader();
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

    if(SCardBeginTransaction(card_handle_) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantStartTransaction);
        releaseCardReader();
        return;
    }

    QByteArray data = "";
    QByteArray fulldata;
    int lastSymbolCount = 0;
    for(int i = 0; i < blockAdresses.size(); i++)
    {
        blockAdress = blockAdresses[i];

        if(!blockAuthenticate(blockAdress))
        {
            emit cardReaderError(CardReaderError::AuthError);
            releaseCardReader();
            return;
        }

        if(!readBlockData(blockAdress, data))
        {
            emit cardReaderError(CardReaderError::ReadError);
            releaseCardReader();
            return;
        }
        fulldata.append(data);

        int lastSymbol = data.indexOf(BRACKET_2);
        if(lastSymbol != -1)
        {
            lastSymbolCount++;
            if(lastSymbolCount == 2)
            {
                break;
            }
        }

    }
    qDebug()<<"fulldata "<<QString(fulldata);
    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

    if(SCardEndTransaction(card_handle_, SCARD_LEAVE_CARD) != SCARD_S_SUCCESS)
    {
        emit cardReaderError(CardReaderError::CantEndTransaction);
        releaseCardReader();
        return;
    }

    releaseCardReader();
    emit userReadSuccess(fulldata);
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
    
    if(SCardListReadersW(card_context_, NULL,(LPWSTR)&mszReaders,&dwReaders) != SCARD_S_SUCCESS)
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
    uint8_t bytes[10] = {0xff, 0x86, 0x00, 0x00, 0x05, 0x01, 0x00, blockNumber/* Block number */,keyType, keyLocation};
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

    uint8_t bytes[5] = {0xff, 0xB0, 0x00, blockNumber/* Block number */,bytesNum/* bytes */};
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
    {
        return false;
    }
    // qDebug()<<"size:  "<<cbRecv;
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
    const int size = 5 + 16;
    uint8_t bytes[size];// = {0xff, 0xD6, 0x00, blockNumber/* Block number */, 0x10/* bytes */, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    bytes[0] = 0xff;
    bytes[1] = 0xD6;
    bytes[2] = 0x00;
    bytes[3] = blockNumber;
    bytes[4] = 0x10;

    for(int i = 5; i < size; i++)
    {
        bytes[i] = data[i-5];//userIdHex[i-5];
    }

    return SCardTransmit(card_handle_, protocol, bytes,  sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::beepCommand(bool enabled)
{
    if(!cardPreparedSuccess())
    {
        return false;
    }

    BYTE pbRecv[MAX_APDU_SIZE];
    DWORD cbRecv = MAX_APDU_SIZE;
    uint8_t bytes[5] = {0xff, 0x00, 0x52, enabled ? 0xff: 0x00, 0x00};
    return SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
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
