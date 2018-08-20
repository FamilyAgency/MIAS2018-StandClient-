#include "MindwaveReaderSerial.h"

MindwaveReaderSerial::MindwaveReaderSerial(QObject *parent) : MindwaveReaderBase(parent)
{
    serialPort = new QSerialPort();
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));


    reconnectTimer = new QTimer(this);
    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(onReconnectHandle()));

}

MindwaveReaderSerial::~MindwaveReaderSerial()
{
    if(serialPort)
    {
        serialPort->close();
        disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        disconnect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));

        delete serialPort;
    }
}

void MindwaveReaderSerial::start()
{
    startReading(0);
}

void MindwaveReaderSerial::startReading(int modelIndex)
{
    QString portName = mindwaveConfig.com;
    serialPort->setPortName(portName);
    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    //    serialPort->setDataBits(QSerialPort::Data8);
    //    serialPort->setParity(QSerialPort::NoParity);
    //    serialPort->setStopBits(QSerialPort::OneStop);
    //    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        //tryReconnect();
        qDebug()<<"serialPort opening error";
    }
    else
    {
        qDebug()<<"serialPort opened";

        // serialPort->setBaudRate(QSerialPort::Baud57600);
    }
}

void MindwaveReaderSerial::onReadyRead()
{
    //qDebug()<<"onReadyRead ";

    QByteArray bytes = serialPort->readAll();
    dataRecieve(bytes);
}

void MindwaveReaderSerial::onReadError(QSerialPort::SerialPortError serialPortError)
{
    qDebug()<<"serialPortError "<< serialPortError;
    if (serialPortError == QSerialPort::ReadError)
    {

    }

   // tryReconnect();
}

void MindwaveReaderSerial::setConfig(const MindwaveConfig& config)
{
    MindwaveReaderBase::setConfig(config);
    // client->setConfig(mindwaveConfig.getSerialConfig());
}

void MindwaveReaderSerial::onConnectionSuccess()
{
    MindwaveReaderBase::onConnectionSuccess();
}

void MindwaveReaderSerial::writeCommand()
{
    QByteArray mindWaveControlInfo;
    mindWaveControlInfo.append(0x02);//command byte
    writeSerialData(mindWaveControlInfo);
}

void MindwaveReaderSerial::writeSerialData(const QByteArray &data)
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

void MindwaveReaderSerial::tryReconnect()
{
    if(!serialPort->isOpen())
    {
        reconnectTimer->stop();
        reconnectTimer->start(1000);
    }

}

void MindwaveReaderSerial::onReconnectHandle()
{
    reconnectTimer->stop();
    startReading(0);
}







