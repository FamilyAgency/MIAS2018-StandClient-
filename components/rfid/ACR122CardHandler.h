#ifndef ACR122CARDHANDLER_H
#define ACR122CARDHANDLER_H

#include <QObject>
#include <QTimer>
#include "WINSCARD.H"
#include "components/RFIDComponent.h"

class ACR122CardHandler : public RFIDComponent
{
    Q_OBJECT
public:
    explicit ACR122CardHandler(QObject *parent = nullptr);
    Q_INVOKABLE virtual void startReading() override;
    Q_INVOKABLE virtual void startWriting(const QString& data) override;
    Q_INVOKABLE void startWriting(int id, const QString& name, const QString& surname, const QString& phone, const QString& email);
    Q_INVOKABLE virtual void stopAll() override;
    Q_INVOKABLE bool beepCommand(bool enabled);
    //Q_INVOKABLE void getCardAttributes();
    //Q_INVOKABLE void resetCard();

    enum class WriteValidation
    {
        None,
        IdOnly,
        AllData
    };

    enum class CardReaderError
    {
        CantStartTransaction,
        CantEndTransaction,
        LoadKeyError,
        NoCardReader,
        NoCard,
        AuthError,
        WriteError,
        ReadError,
        UnknownError,
    };
    Q_ENUMS(CardReaderError)

private:
    const int ONE_BLOCK_SIZE = 16;
    QTimer* connectTimer;
    WriteValidation writeValidation = WriteValidation::AllData;

    LPCSCARD_IO_REQUEST protocol = SCARD_PCI_T1;
    SCARDCONTEXT card_context_;
    SCARDHANDLE card_handle_;

    QVector<uint8_t> blockAdresses;
    uint8_t blockAdress = 0x01;
    const uint8_t keyType = 0x60; //0x60 /*TypeA */
    uint8_t keyLocation = 0x00;//0x01
    QString userData = "";
    QString blockZeroData = "";

    void readId();
    void readAllData();

    void fillBlockAdresses();
    void timerRestart();
    bool cardPreparedSuccess();
    void releaseCardReader();
    int getBlocksNeedForWriting(const QByteArray& cardData);
    void alignData(QByteArray& cardData);

    bool establishContext();
    bool cardConnect();

    bool checkIsDeviceConnected();
    //bool getFirmVer(QString& ver);
    //bool getCardUid(QString& cardUid);

    bool loadKey();
    bool blockAuthenticate(uint8_t blockNumber);
    bool readBlockData(uint8_t blockNumber, QByteArray& data);
    bool writeBlockData(uint8_t blockNumber, const QByteArray& data);

    int readerTimeout = 2000;
    int checkMills = 100;

    CardReaderState cardReaderState;
    void setCardReaderState(CardReaderState state);   

signals:
    void cardReaderError(CardReaderError);

    void unknownError();
    void readingCardError();

    void newData(const QString& data);
    void newTag(int id);

    void userWriteSuccess();
    void userWriteError();

    void cardReaderStateChanged(CardReaderState state);

private slots:
    void onReadingUpdate();
    void onWritingUpdate();
    void resetReadingState();
    void onUserWriteSuccess();
};

#endif // ACR122CARDHANDLER_H
