#include "ArduinoDataReader.h"
#include <QSerialPortInfo>

ArduinoDataReader::ArduinoDataReader(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort();
}

void ArduinoDataReader::setConfig(const ArduinoConfig& config)
{
    arduinoConfig = config;
}

QVariantList ArduinoDataReader::getPortsAvailable() const
{
    QVariantList info;
    QSerialPortInfo serialPortInfo;

    qDebug()<<"port names ======================";
    auto ports = serialPortInfo.availablePorts();
    for(auto port: ports)
    {
        info.append(port.portName() + " " + port.description());
    }
    qDebug()<<"======================";

    return info;
}

QString ArduinoDataReader::getPortNameByModelIndex(int modelIndex) const
{
    QSerialPortInfo serialPortInfo;
    auto ports = serialPortInfo.availablePorts();

    if(ports.length() > modelIndex)
    {
        return ports[modelIndex].portName();
    }

    return "";
}

void ArduinoDataReader::startReading(int modelIndex)
{
    auto portName = getPortNameByModelIndex(modelIndex);
    serialPort->setPortName(portName);

    qDebug()<<"startReading "<<modelIndex<<portName;

    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    if (!serialPort->open(QIODevice::ReadOnly))
    {
        qDebug()<<"serialPort opening error";
    }
    else
    {
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));

        //timer = new QTimer(this);
       // connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        //timer->start(taskTimerMills);
    }
}

void ArduinoDataReader::onReadyRead()
{
    readData.append(serialPort->readAll());
}

void ArduinoDataReader::onReadError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError)
    {

    }
}

//void ArduinoDataReader::onUpdate()
//{
//    if (!readData.isEmpty())
//    {

//    }
//    else
//    {

//    }
//}
