#include "MindwaveReaderSerial.h"

MindwaveReaderSerial::MindwaveReaderSerial(QObject *parent) : MindwaveReaderBase(parent)
{  

}

MindwaveReaderSerial::~MindwaveReaderSerial()
{
    disconnect(serialWorkerThread, SIGNAL(started()), serialThread, SLOT(startReading()));
    disconnect(serialThread, SIGNAL(dataRecieve(const QByteArray&)), this, SLOT(onDataRecieve(const QByteArray&)));

    serialWorkerThread->quit();
    serialWorkerThread->wait();

   // emit destroyMindwaveReader();
}

void MindwaveReaderSerial::start()
{
    serialWorkerThread = new QThread(this);
    serialThread = new SerialThread();
    serialThread->setPortName(mindwaveConfig.com);
    connect(serialWorkerThread, SIGNAL(started()), serialThread, SLOT(startReading()));
    connect(serialWorkerThread, SIGNAL(finished()), serialThread, SLOT(deleteLater()));

    connect(serialThread, SIGNAL(dataRecieve(const QByteArray&)), this, SLOT(onDataRecieve(const QByteArray&)));
    connect(this, SIGNAL(destroyMindwaveReader()), serialWorkerThread, SLOT(quit()));

    serialThread->initThread(serialWorkerThread);

    serialThread->moveToThread(serialWorkerThread);
    serialWorkerThread->start();
}

void MindwaveReaderSerial::onDataRecieve(const QByteArray& bytes)
{  
     dataRecieve(bytes);
}

void MindwaveReaderSerial::setConfig(const MindwaveConfig& config)
{
    MindwaveReaderBase::setConfig(config);
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

//    uint64_t bytesWritten = serialPort->write(writeData);
//    qDebug() << "MindWaveMobile Data Sent...";

//    if (bytesWritten == -1)
//    {
//        qDebug() << "Failed to write the data to port";
//        return;
//    }
//    else if (bytesWritten != writeData.size())
//    {
//        qDebug() << "Failed to write all the data to port";
//        return;
//    }
//    else if (!serialPort->waitForBytesWritten(5000))
//    {
//        qDebug() << "Operation timed out or an error occurred for port";
//        return;
//    }

    qDebug() << "Data Write Sucessfull";
    return;
}
