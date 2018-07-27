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
    Q_INVOKABLE virtual void startWriting(int userId) override;
    Q_INVOKABLE virtual void stopAll() override;
    Q_INVOKABLE bool beepCommand(bool enabled);
    Q_INVOKABLE void getCardAttributes();

private:
    QTimer* connectTimer;

    LPCSCARD_IO_REQUEST protocol = SCARD_PCI_T1;
    SCARDCONTEXT card_context_;
    SCARDHANDLE card_handle_;
    QVector<uint8_t> blockAdresses;//[11];// = {0x01,  0x01,  0x02,  0x04,  0x05,  0x06,  0x08,  0x09,  0x010,  0x012,  0x013};
    uint8_t blockAdress = 0x01;
    int userId = 100;
   // QString deviceName = "ACS ACR122 0";
    void fillBlockAdresses();

    bool establishContext();
    bool cardConnect();

    bool checkIsDeviceConnected();
    bool getFirmVer(QString& ver);
    bool getCardUid(QString& cardUid);

    bool loadKey();
    bool blockAuthenticate(uint8_t blockNumber);
    bool readBlockData(uint8_t blockNumber, QString& data);
    bool writeBlockData(uint8_t blockNumber, const QByteArray& data);
    bool writeBlockId(uint8_t blockNumber, int id);

    QVector<int> getDigitsArrayFromInt(int id) const;

    int readerTimeout = 2000;
    int checkMills = 500;

    CardReaderState cardReaderState;
    void setCardReaderState(CardReaderState state);   

signals:
    void noCard();
    void noCardReader();
    void loadKeyError();
    void authError();
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
};

#endif // ACR122CARDHANDLER_H
