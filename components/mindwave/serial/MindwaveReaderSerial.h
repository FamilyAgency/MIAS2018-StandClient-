#ifndef MINDWAVEREADERSERIAL_H
#define MINDWAVEREADERSERIAL_H

#include <QSerialPort>
#include <QThread>
#include "SerialThread.h"
#include "components/mindwave/MindwaveReaderBase.h"

class MindwaveReaderSerial : public MindwaveReaderBase
{
    Q_OBJECT
public:
    explicit MindwaveReaderSerial(QObject *parent = nullptr);
    virtual ~MindwaveReaderSerial();
    virtual void start() override;

private:
    QByteArray readData;
    SerialThread* serialThread = nullptr;
    QThread* serialWorkerThread = nullptr;

protected slots:
    void onDataRecieve(const QByteArray& dataReady);
    void onConnectionError();
    void onNoDataTimeout();
};

#endif // MINDWAVEREADERSERIAL_H
