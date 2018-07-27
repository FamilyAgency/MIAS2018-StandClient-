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
    Q_INVOKABLE virtual void stopAll() override;
    Q_INVOKABLE bool beepCommand(bool enabled);
    Q_INVOKABLE void getCardAttributes();
    Q_INVOKABLE void resetCard();

private:
    QTimer* connectTimer;

    LPCSCARD_IO_REQUEST protocol = SCARD_PCI_T1;
    SCARDCONTEXT card_context_;
    SCARDHANDLE card_handle_;

    QVector<uint8_t> blockAdresses;
    uint8_t blockAdress = 0x01;
    const uint8_t keyType = 0x60; //0x60 /*TypeA */
    uint8_t keyLocation = 0x00;//0x01
    QString userData = "";

    void fillBlockAdresses();

    bool establishContext();
    bool cardConnect();

    bool checkIsDeviceConnected();
    bool getFirmVer(QString& ver);
    bool getCardUid(QString& cardUid);

    bool loadKey();
    bool blockAuthenticate(uint8_t blockNumber);
    bool readBlockData(uint8_t blockNumber, QByteArray& data);
    bool writeBlockData(uint8_t blockNumber, const QByteArray& data);
    bool writeBlockId(uint8_t blockNumber, int id);

    QVector<int> getDigitsArrayFromInt(int id) const;

    int readerTimeout = 2000;
    int checkMills = 100;

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
