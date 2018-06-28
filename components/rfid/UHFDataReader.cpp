#include "UHFDataReader.h"

UHFDataReader::UHFDataReader(QObject *parent) : BaseRFIDDataReader(parent)
{
    beepOnCommand.append(char(0xA0));
    beepOnCommand.append(char(0x04));
    beepOnCommand.append(char(0x01));
    beepOnCommand.append(char(0x7A));
    beepOnCommand.append(char(0x01));
    beepOnCommand.append(char(0xE0));

    beepOffCommand.append(char(0xA0));
    beepOffCommand.append(char(0x04));
    beepOffCommand.append(char(0x01));
    beepOffCommand.append(char(0x7A));
    beepOffCommand.append(char(0x00));
    beepOffCommand.append(char(0xE1));

    readCommand.append(char(0xA0));//head
    readCommand.append(char(0x04));//len
    readCommand.append(char(0xFF));//adress

    readCommand.append(char(0x89));
    readCommand.append(char(0x01));
    readCommand.append(char(0xD3));
}

void UHFDataReader::startReading(int modelIndex)
{
    auto portName = getPortNameByModelIndex(modelIndex);
    serialPort->setPortName(portName);

    qDebug()<<"startReading "<<modelIndex<<portName;

    auto serialPortBaudRate = QSerialPort::Baud115200;
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

        serialPort->write(beepOnCommand);

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        timer->start(taskTimerMills);
    }
}

void UHFDataReader::onReadyRead()
{
    qDebug()<<"!!!!!!!!serialPort read"<<serialPort->readAll();
    readData.append(serialPort->readAll());
}

void UHFDataReader::onUpdate()
{
    serialPort->write(readCommand);
}

