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
    ~ACR122CardHandler();

    virtual void setConfig(ConfigPtr config) override;

    virtual void startReading() override;
    Q_INVOKABLE void startReadingId() override;
    Q_INVOKABLE void startReadingAllData() override;

    Q_INVOKABLE virtual void startWriting(const QString& data) override;
    Q_INVOKABLE void startWriting(int id, const QString& name, const QString& surname, const QString& phone, const QString& email);
    Q_INVOKABLE virtual void stopAll() override;
    Q_INVOKABLE bool beepCommandDirect(bool enabled);
    Q_INVOKABLE bool getStatusCommand();

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
        CardParsing,
        DataFormatError,
        UnknownError,
    };
    Q_ENUMS(CardReaderError)

private:
    static const DWORD MAX_APDU_SIZE = 255;
    const int ONE_BLOCK_SIZE = 16;
    const char DELIM = ',';
    const char BRACKET_1 = '{';
    const char BRACKET_2 = '}';
    QTimer* connectTimer;
    WriteValidation writeValidation = WriteValidation::AllData;

    LPCSCARD_IO_REQUEST protocol = SCARD_PCI_T1;
    SCARDCONTEXT card_context_;
    SCARDHANDLE card_handle_;

    QVector<uint8_t> blockAdresses;
    uint8_t blockAdress = 0x01;
    const uint8_t keyType = 0x60; //0x60 /*TypeA */ 0x61 /*TypeB */
    uint8_t keyLocation = 0x00;//0x01
    QString blockZeroData = "";

    bool readIdOnly = true;
    bool startCommandsInit = false;

    QString lastUserId;
    QString lastUserData;

    bool beepCommand(bool enabled);
    void runStartCommands();

    void readId();
    void readAllData();

    void fillBlockAdresses();
    WriteValidation validationFromString(const QString& value);
    bool formatUserData(int id, const QString& name, const QString& surname, const QString& phone, const QString& email);

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

    bool compareAllData(const QString& data, const QString& lastUserData);


    void startValidation(const QString& data);

    void blockZeroDataInit();

    int readerTimeout = 2000;
    int checkMills = 100;

signals:
    void cardReaderError(CardReaderError error);
    void userWriteSuccess();   
    void validationSuccess();
    void validationFailed();

private slots:
    void onReadingUpdate();
    void onWritingUpdate();
    void resetReadingState();
    void onUserWriteSuccess();
    void onCardReaderError(CardReaderError);
    void onUserIdReadSuccess(const QString&);
    void onUserDataReadSuccess(const QString&);

};

#endif // ACR122CARDHANDLER_H
