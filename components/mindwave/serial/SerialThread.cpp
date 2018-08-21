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

void SerialThread::startReading()
{
    serialPort->setPortName(portName);
    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        tryReconnect();
        qDebug()<<"serialPort opening error";
    }
    else
    {
        qDebug()<<"serialPort opened";
    }

    noDataTimer->start(2000);
}

void SerialThread::onReadyRead()
{
    //qDebug()<<"onReadyRead";
    noDataTimer->start(2000);
    QByteArray bytes = serialPort->readAll();
    emit dataRecieve(bytes);
}

void SerialThread::onReadError(QSerialPort::SerialPortError serialPortError)
{
    qDebug()<<"serialPortError "<< serialPortError;
    if (serialPortError == QSerialPort::ReadError)
    {

    }
}

void SerialThread::onNoDataTimerHandle()
{
    qDebug()<<"timeout ";
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
    reconnectTimer->start(1000);
}

void SerialThread::onReconnectHandle()
{
    reconnectTimer->stop();
    startReading();
}

