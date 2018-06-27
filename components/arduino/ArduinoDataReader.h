#ifndef ARDUINODATAREADER_H
#define ARDUINODATAREADER_H

#include <QSerialPort>
#include <QObject>
#include <QTimer>
#include "config/Config.h"

class ArduinoDataReader : public QObject
{
    Q_OBJECT

public:
    explicit ArduinoDataReader(QObject *parent = nullptr);

    void startReading(int modelIndex);
    void setConfig(const ArduinoConfig& config);
    QVariantList getPortsAvailable() const;

private:
     const int taskTimerMills = 1000;

     ArduinoConfig arduinoConfig;
     bool _connected = false;

     QSerialPort* serialPort = nullptr;
     QByteArray readData;
     QTimer* timer;

     QString getPortNameByModelIndex(int modelIndex) const;

signals:
     void dataReaded(const QString&);
     void readError();

private slots:
     void onReadyRead();
     void onReadError(QSerialPort::SerialPortError serialPortError);
};

#endif // ARDUINODATAREADER_H
