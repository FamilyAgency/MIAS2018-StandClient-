#include "BaseRFIDDataReader.h"
#include <QSerialPortInfo>

BaseRFIDDataReader::BaseRFIDDataReader(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort();
}

void BaseRFIDDataReader::setConfig(const RFIDConfig& config)
{
    rfidConfig = config;
}

QVariantList BaseRFIDDataReader::getPortsAvailable() const
{
    QVariantList info;
    QSerialPortInfo serialPortInfo;

    qDebug()<<"port names ======================";
    auto ports = serialPortInfo.availablePorts();
    for(auto port: ports)
    {
        info.append(port.portName() + " " /*+ port.description() + " "*/ +  port.manufacturer());
         qDebug()<<"port name: " +  port.portName();
         qDebug()<<"port description: " +  port.description();
         qDebug()<<"port manufacturer: " +  port.manufacturer();
         qDebug()<<"port systemLocation: " +  port.systemLocation();
         qDebug()<<"port serialNumber: " +  port.serialNumber();
         qDebug()<<"port vendorIdentifier: " +  port.vendorIdentifier();
         qDebug()<<"port productIdentifier: " +  port.productIdentifier();
    }
    qDebug()<<"======================";

    return info;
}

QString BaseRFIDDataReader::getPortNameByModelIndex(int modelIndex) const
{
    QSerialPortInfo serialPortInfo;
    auto ports = serialPortInfo.availablePorts();

    if(ports.length() > modelIndex)
    {
        return ports[modelIndex].portName();
    }

    return "";
}

void BaseRFIDDataReader::startReading(int modelIndex)
{
    auto portName = getPortNameByModelIndex(modelIndex);
    serialPort->setPortName(portName);

    qDebug()<<"startReading "<<modelIndex<<portName;

    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        qDebug()<<"serialPort opening error";
    }
    else
    {
        qDebug()<<"serialPort opened";
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));
    }
}

void BaseRFIDDataReader::onReadyRead()
{
     qDebug()<<"serialPort read"<<serialPort->readAll();
    readData.append(serialPort->readAll());
}

void BaseRFIDDataReader::onReadError(QSerialPort::SerialPortError serialPortError)
{
    qDebug()<<"serialPortError "<< serialPortError;
    if (serialPortError == QSerialPort::ReadError)
    {

    }
}
