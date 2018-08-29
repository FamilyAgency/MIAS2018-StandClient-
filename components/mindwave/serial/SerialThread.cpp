#include "SerialThread.h"
#include <QDebug>
#include <QSerialPortInfo>

SerialThread::SerialThread(QObject *parent): QObject(parent)
{

}

void SerialThread::initThread(QThread* thread)
{
    serialPort = new QSerialPort();
    serialPort->moveToThread(thread);
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));

    reconnectTimer = new QTimer(this);
    //reconnectTimer->moveToThread(thread);
    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(onReconnectHandle()));

    noDataTimer = new QTimer(this);
   // noDataTimer->moveToThread(thread);
    connect(noDataTimer, SIGNAL(timeout()), this, SLOT(onNoDataTimerHandle()));

}

SerialThread::~SerialThread()
{
    qDebug()<<"Destroy thread";
    serialPort->close();

    disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    disconnect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));
    disconnect(reconnectTimer, SIGNAL(timeout()), this, SLOT(onReconnectHandle()));
    disconnect(noDataTimer, SIGNAL(timeout()), this, SLOT(onNoDataTimerHandle()));

    if(serialPort)
    {
        delete serialPort;
    }

    if(reconnectTimer)
    {
        delete reconnectTimer;
    }

    if(noDataTimer)
    {
        delete noDataTimer;
    }
}

void SerialThread::setPortName(const QString& value)
{
    portName = value;
}

void SerialThread::setNoDataTimeoutMills(int value)
{
    noDataTimeoutMills = value;
}

void SerialThread::setReconnectionMills(int value)
{
    reconnectionMills = value;
}

void SerialThread::startReading()
{
    qDebug()<<"connect serial to "<<portName;
    serialPort->setPortName(portName);
    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);
    //serialPort->setFlowControl(QSerialPort::HardwareControl);   

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        emit connectionError();
        tryReconnect();
        qDebug()<<"serialPort opening error";
    }
    else
    {
        emit connectionSuccess();
       // writeCommand();
       // serialPort->setBaudRate(QSerialPort::Baud57600);
        qDebug()<<"serialPort opened";
    }

    noDataTimer->start(noDataTimeoutMills);
}

void SerialThread::onReadyRead()
{
    noDataTimer->stop();
    noDataTimer->start(noDataTimeoutMills);
    QByteArray bytes = serialPort->readAll();

    emit dataRecieve(bytes);
}

void SerialThread::onReadError(QSerialPort::SerialPortError serialPortError)
{
    //qDebug()<<"serialPortError "<< serialPortError;
}

void SerialThread::onNoDataTimerHandle()
{
    qDebug()<<"timeout ";
    emit noDataTimeout();
    noDataTimer->stop();
    tryReconnect();
}

void SerialThread::tryReconnect()
{
    qDebug()<<"tryReconnect ";
    if(serialPort->isOpen())
    {
        serialPort->close();
    }

    reconnectTimer->stop();
    reconnectTimer->start(reconnectionMills);
}

void SerialThread::onReconnectHandle()
{
    reconnectTimer->stop();
    startReading();
}

void SerialThread::writeCommand()
{
    QByteArray mindWaveControlInfo;
    mindWaveControlInfo.append(0x02);//command byte
    writeSerialData(mindWaveControlInfo);
}

void SerialThread::writeSerialData(const QByteArray &data)
{
    if (data.count() > 169)
    {
        qDebug() << "Payload too large. Max payload size is 169 Bytes";
        return;
    }

    // create ThinkGearPacket
    QByteArray writeData;
    writeData.append(0xAA);              // SYNC BYTE
    writeData.append(0xAA);              // SYNC BYTE
    writeData.append(data.size()&0xFF);  // PAYLOAD LENGTH
    writeData.append(data);              // PAYLOAD

    // calculate CHKSUM
    char chksum = 0;
    for (const auto &x : data)
    {
        chksum += x;
    }
    chksum &= 0xFF;
    chksum = (~chksum) & 0xFF;

    writeData.append(chksum);  // CHKSUM

    uint64_t bytesWritten = serialPort->write(writeData);
    qDebug() << "MindWaveMobile Data Sent...";

    if (bytesWritten == -1)
    {
        qDebug() << "Failed to write the data to port";
        return;
    }
    else if (bytesWritten != writeData.size())
    {
        qDebug() << "Failed to write all the data to port";
        return;
    }
    else if (!serialPort->waitForBytesWritten(5000))
    {
        qDebug() << "Operation timed out or an error occurred for port";
        return;
    }

    qDebug() << "Data Write Sucessfull";
    return;
}


