#ifndef MINDWAVEREADERSERIAL_H
#define MINDWAVEREADERSERIAL_H

#include <QSerialPort>
#include "components/mindwave/MindwaveReaderBase.h"

class MindwaveReaderSerial : public MindwaveReaderBase
{
    Q_OBJECT
public:
    explicit MindwaveReaderSerial(QObject *parent = nullptr);
    virtual ~MindwaveReaderSerial();

    virtual void startReading(int modelIndex);

    virtual void setConfig(const MindwaveConfig& value) override;
    virtual void start() override;

private:
    QSerialPort* serialPort = nullptr;
    QByteArray readData;
    void writeSerialData(const QByteArray &data);
    void writeCommand();

protected slots:
    virtual void onConnectionSuccess();

private slots:
    virtual void onReadyRead();
    void onReadError(QSerialPort::SerialPortError serialPortError);
};

#endif // MINDWAVEREADERSERIAL_H
