#include "SerialThread.h"
#include <QDebug>

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
    serialPort->setPortName(portName);
    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        emit connectionError();
        tryReconnect();
       // qDebug()<<"serialPort opening error";
    }
    else
    {
        emit connectionSuccess();
       // qDebug()<<"serialPort opened";
    }

    noDataTimer->start(noDataTimeoutMills);
}

void SerialThread::onReadyRead()
{
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
   // qDebug()<<"timeout ";
    emit noDataTimeout();
    noDataTimer->stop();
    tryReconnect();
}

void SerialThread::tryReconnect()
{
   // qDebug()<<"tryReconnect ";
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

