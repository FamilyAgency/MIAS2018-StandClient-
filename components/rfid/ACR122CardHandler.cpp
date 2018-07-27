#include "ACR122CardHandler.h"
#include <qDebug>
#include <QSharedPointer>
#define MAX_APDU_SIZE 255

ACR122CardHandler::ACR122CardHandler(QObject *parent) : RFIDComponent(parent)
{
    connectTimer = new QTimer(this);
    fillBlockAdresses();
}

void ACR122CardHandler::fillBlockAdresses()
{
    int k = 0;
    for(int i = 0; i< 64; i++)
    {
        if(k++ == 3)
        {
            k =0;
        }
        else
        {
            QString hex = QString::number(i, 16);
            bool ok;
            const unsigned int parsedValue = hex.toUInt(&ok, 16);
            blockAdresses.push_back(parsedValue);
            // qDebug()<<hex<<parsedValue;
        }
    }
    blockAdresses.pop_front();
    // blockAdresses.clear();
    /// blockAdresses.push_back(0x04);
    //  blockAdresses.push_back(0x05);

    blockAdress = blockAdresses[0];
}

void ACR122CardHandler::startReading()
{
    setCardReaderState(CardReaderState::Reading);
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
    connect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
    connectTimer->start(checkMills);
}

void ACR122CardHandler::startWriting(const QString& data)
{
    setCardReaderState(CardReaderState::Writing);
    userData = data;
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    disconnect(connectTimer, SIGNAL(timeout()), this, SLOT(onReadingUpdate()));
    connect(connectTimer, SIGNAL(timeout()), this, SLOT(onWritingUpdate()));
    connectTimer->start(checkMills);
}

void ACR122CardHandler::stopAll()
{
    setCardReaderState(CardReaderState::Stopped);
    connectTimer->stop();
}

void ACR122CardHandler::onWritingUpdate()
{
    if(!establishContext())
    {
        emit noCardReader();
        return;
    }

    if(!checkIsDeviceConnected())
    {
        emit noCardReader();
        return;
    }

    if(!cardConnect())
    {
        emit noCard();
        return;
    }

    if(!loadKey())
    {
        emit loadKeyError();
        return;
    }

    connectTimer->stop();

    if(SCardBeginTransaction(card_context_) == SCARD_S_SUCCESS)
    {
        qDebug()<<"transaction started: ";
        return;
    }

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
  //  QByteArray cardData = "99999,Константин,Константин,Константин,Константин,Константин,Константин,9056784575,yurikblech@gmail.com/t";
    QByteArray cardData = "/t" + userData.toUtf8() + "/t";

    qDebug()<<"write bytes: "<<cardData.size();

    int addBlock = cardData.size() % 16 != 0 ? 1 : 0;
    int blocksNeeded = cardData.size()/16 + addBlock;
    qDebug()<<"blocksNeeded: "<<blocksNeeded;


    int blockOffset = 0;
    for(int i = 0; i < blocksNeeded; i++)
    {
        blockAdress = blockAdresses[i];

        if(!blockAuthenticate(blockAdress))
        {
            emit authError();
            return;
        }

        QByteArray blockData;
        for(int i = 0; i < 16; i++)
        {
            blockData[i] = cardData[blockOffset + i];
        }
        blockOffset += 16;
        qDebug()<<"write to block: "<<blockAdress<<" : "<<blockData;

        if(!writeBlockData(blockAdress, blockData))
        {
            userWriteError();
            return;
        }
    }

    if(SCardEndTransaction(card_context_, SCARD_LEAVE_CARD)== SCARD_S_SUCCESS)
    {
        qDebug()<<"transaction closed: ";
        return;
    }

    SCardDisconnect(card_handle_, SCARD_UNPOWER_CARD);
    //  LPCWSTR cardReaderName = reinterpret_cast<LPCWSTR>(rfidConfig().type.unicode());
    //  SCardFreeMemory(card_context_, cardReaderName);
    // SCardDisconnect(card_handle_, SCARD_LEAVE_CARD);
    SCardReleaseContext(card_context_);
    userWriteSuccess();
    connectTimer->stop();
}

void ACR122CardHandler::onReadingUpdate()
{
    if(!establishContext())
    {
        emit unknownError();
        return;
    }

    if(!checkIsDeviceConnected())
    {
        emit noCardReader();
        return;
    }

    if(!cardConnect())
    {
        emit noCard();
        return;
    }

    if(!loadKey())
    {
        emit loadKeyError();
        return;
    }

    connectTimer->stop();

    if(SCardBeginTransaction(card_context_) == SCARD_S_SUCCESS)
    {
        qDebug()<<"transaction started: ";
        return;
    }

    QByteArray data = "";
    QByteArray fulldata;
    for(int i = 0; i < blockAdresses.size(); i++)
    {
        blockAdress = blockAdresses[i];

        if(!blockAuthenticate(blockAdress))
        {
            emit authError();
            return;
        }

        if(!readBlockData(blockAdress, data))
        {
            emit userWriteError();
            return;
        }
        fulldata.append(data);
       // qDebug()<<"readed from block "<<blockAdress<<": "<<data;
    }
    qDebug()<<"fulldata "<<QString(fulldata);
    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    //rv = SCardDisconnect(hCard, SCARD_UNPOWER_CARD);
    if(SCardEndTransaction(card_context_, SCARD_LEAVE_CARD)== SCARD_S_SUCCESS)
    {
        qDebug()<<"transaction closed: ";
        return;
    }

    SCardDisconnect(card_handle_, SCARD_UNPOWER_CARD);
    //  LPCWSTR cardReaderName = reinterpret_cast<LPCWSTR>(rfidConfig().type.unicode());
    //  SCardFreeMemory(card_context_, cardReaderName);
    // SCardDisconnect(card_handle_, SCARD_LEAVE_CARD);
    SCardReleaseContext(card_context_);


    emit newData(fulldata);

    //    QString data;
    //    if(readBlockData(blockNumber, data))
    //    {
    //        SCardDisconnect(card_handle_, SCARD_LEAVE_CARD);
    //        SCardReleaseContext(card_context_);
    //        emit newTag(data.toInt());
    //        connectTimer->stop();
    //        QTimer::singleShot(readerTimeout, this, SLOT(resetReadingState()));
    //    }
    //    else
    //    {
    //        emit readingCardError();
    //    }
}

void ACR122CardHandler::setCardReaderState(CardReaderState state)
{
    cardReaderState = state;
    emit cardReaderStateChanged(state);
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
    SCardListReadersW(card_context_, NULL,(LPWSTR)&mszReaders,&dwReaders);

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

void ACR122CardHandler::resetCard()
{
    establishContext();

    cardConnect();

    uint8_t bytes[21] = {0xFF, 0xD6, 0x00, 0x03, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF};

    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    if(SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS)
    {
        qDebug()<<"success";
    }
    else
    {
        qDebug()<<"FAILLLLL";
    }
}

//bool ACR122CardHandler::cardStatus()
//{
//    printf("SCardStatus : ");
//       dwReaderLen = MAX_READER_NAME_SIZE;
//       pcReaders = (LPWSTR)malloc(sizeof(char) * MAX_READER_NAME_SIZE);

//       rv = SCardStatus(hCard, pcReaders, &dwReaderLen, &dwState,
//           &dwProt, pbAtr, &dwAtrLen);
//}

bool ACR122CardHandler::readBlockData(uint8_t blockNumber, QByteArray& data)
{
    uint8_t bytesNum = 0x010;
    QString str = QString::number(bytesNum);
   // qDebug()<<"-------------------------------";
   // qDebug()<<"read bytes :" << str.toInt();

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

bool ACR122CardHandler::writeBlockId(uint8_t blockNumber, int id)
{
    //qDebug()<<"xxxxxxxxxxxwriteBlockIdxxxxxxxxxxx";
    int idMaxDigits = 10;
    QVector<int> digitsArray = getDigitsArrayFromInt(id);

    int additionalDigits = idMaxDigits - digitsArray.size();

    for(int i = 0 ; i < additionalDigits; i++)
    {
        digitsArray.push_front(0);
    }

    // qDebug()<<"xxxxxxxxxxxxxxxxxxxxxx";
    for(int i = 0; i < additionalDigits; i++)
    {
        //    qDebug()<<digitsArray[i];
    }
    // qDebug()<<"xxxxxxxxxxxxxxxxxxxxxx";

    const uint8_t bytesNum = 10;
    uint8_t userIdHex[bytesNum];

    for( int i = 0; i < bytesNum; i++)
    {
        userIdHex[i] = digitsArray[i];
    }

    QByteArray cardData = "Konstantin";
    // QByteArray cardData = "Константин";

    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    const int size = 5 + 10;
    uint8_t bytes[size];// = {0xff, 0xD6, 0x00, blockNumber/* Block number */, 0x10/* bytes */, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    bytes[0] = 0xff;
    bytes[1] = 0xD6;
    bytes[2] = 0x00;
    bytes[3] = blockNumber;
    bytes[4] = 0x10;

    for(int i = 5; i < size; i++)
    {
        bytes[i] = cardData[i-5];//userIdHex[i-5];
    }

    return SCardTransmit(card_handle_, protocol, bytes,  sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

bool ACR122CardHandler::getFirmVer(QString& ver)
{
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    uint8_t bytes[5] = {0xff, 0x00, 0x48, 0x00, 0x00};

    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
    {
        return false;
    }

    ver = "";
    for (int i = 0; i < cbRecv - 2; i++)
    {
        ver += QString("%02").arg(pbRecv[i]);
    }

    return true;
}

bool ACR122CardHandler::getCardUid(QString& uid)
{
    DWORD cbRecv = MAX_APDU_SIZE;
    BYTE pbRecv[MAX_APDU_SIZE];
    uint8_t bytes[5] = {0xff, 0xCA, 0x00, 0x00, 0x00};

    if (SCardTransmit(card_handle_, protocol, bytes, sizeof(bytes), NULL, pbRecv, &cbRecv) != SCARD_S_SUCCESS)
    {
        return false;
    }

    uid = "";
    for (int i = 0; i < cbRecv - 2; i++)
    {
        uid += QString("%02").arg(pbRecv[i]);
    }

    return true;
}


bool ACR122CardHandler::beepCommand(bool enabled)
{
    BYTE pbRecv[MAX_APDU_SIZE];
    DWORD cbRecv = MAX_APDU_SIZE;
    //   uint8_t bytes[5] = {0xff, 0x00, 0x52, enabled ? 0xff: 0x00, 0x00};
    uint8_t bytes[5] = {0xff, 0x00, 0x52, 0x00, 0x00};
    return SCardTransmit(card_handle_, protocol, bytes,  sizeof(bytes), NULL, pbRecv, &cbRecv) == SCARD_S_SUCCESS;
}

QVector<int> ACR122CardHandler::getDigitsArrayFromInt(int id) const
{
    int temp = id;
    QVector<int> digitsArray;

    do
    {
        digitsArray.push_front(temp % 10);
        temp /= 10;
    }
    while (temp > 0);

    return  digitsArray;
}

void ACR122CardHandler::getCardAttributes()
{
    if(!establishContext())
    {
        emit noCardReader();
        return;
    }

    if(!checkIsDeviceConnected())
    {
        emit noCardReader();
        return;
    }

    if(!cardConnect())
    {
        emit noCard();
        return;
    }

    LPBYTE   pbAttr = NULL;
    DWORD    cByte = SCARD_AUTOALLOCATE;
    DWORD    i;
    LONG	 lRetValue;

    // Gets the current reader attributes for the given handle.
    if( SCardGetAttrib(
                card_context_,  // Card handle.
                SCARD_ATTR_VENDOR_NAME, // Attribute identifier.
                (LPBYTE)&pbAttr,    // Attribute buffer.
                &cByte)== SCARD_S_SUCCESS)

    {
        qDebug()<<"AttrSuccess";
    }
    else
    {
        qDebug()<<"Attr failed";
    }
}
