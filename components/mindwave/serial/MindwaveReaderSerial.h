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

    virtual void setConfig(const MindwaveConfig& value) override;
    virtual void start() override;

private:
    QByteArray readData;
    void writeSerialData(const QByteArray &data);
    void writeCommand();

    SerialThread* serialThread;
    QThread* serialWorkerThread;

protected slots:
    virtual void onConnectionSuccess();
    void onDataRecieve(const QByteArray& dataReady);

signals:
    void destroyMindwaveReader();

//private slots:
  //  virtual void onReadyRead();
};

#endif // MINDWAVEREADERSERIAL_H
