#ifndef BASERFIDDATAREADER_H
#define BASERFIDDATAREADER_H

#include <QSerialPort>
#include <QObject>
#include <QTimer>
#include "config/Config.h"

class BaseRFIDDataReader : public QObject
{
    Q_OBJECT

public:
    explicit BaseRFIDDataReader(QObject *parent = nullptr);

    virtual void startReading(int modelIndex);
    void setConfig(const RFIDConfig& config);
    QVariantList getPortsAvailable() const;

protected:
     RFIDConfig rfidConfig;
     bool _connected = false;

     QSerialPort* serialPort = nullptr;
     QByteArray readData;
     QString getPortNameByModelIndex(int modelIndex) const;

signals:
     void dataReaded(const QString&);
     void readError();

private slots:
     virtual void onReadyRead();
     void onReadError(QSerialPort::SerialPortError serialPortError);

};

#endif // BASERFIDDATAREADER_H
