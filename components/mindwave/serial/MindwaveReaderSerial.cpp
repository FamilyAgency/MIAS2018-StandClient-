#include "MindwaveReaderSerial.h"

MindwaveReaderSerial::MindwaveReaderSerial(QObject *parent) : MindwaveReaderBase(parent)
{  

}

MindwaveReaderSerial::~MindwaveReaderSerial()
{
    qDebug()<<"Destroy MindwaveReaderSerial";

    disconnect(serialWorkerThread, SIGNAL(started()), serialThread, SLOT(startReading()));
    disconnect(serialWorkerThread, SIGNAL(finished()), serialThread, SLOT(deleteLater()));

    disconnect(serialThread, SIGNAL(dataRecieve(const QByteArray&)), this, SLOT(onDataRecieve(const QByteArray&)));
    disconnect(serialThread, SIGNAL(connectionError()), this, SLOT(onConnectionError()));
    disconnect(serialThread, SIGNAL(noDataTimeout()), this, SLOT(onNoDataTimeout()));
    disconnect(serialThread, SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));

    serialWorkerThread->quit();
    serialWorkerThread->wait();

    qDebug()<<"Destroy serialWorkerThread";
}

void MindwaveReaderSerial::start()
{
    if(!serialThread)
    {
        serialWorkerThread = new QThread(this);
        serialThread = new SerialThread();
        serialThread->setPortName(mindwaveConfig.com);
        serialThread->setNoDataTimeoutMills(mindwaveConfig.timeoutMills);
        serialThread->setReconnectionMills(1000);

        connect(serialWorkerThread, SIGNAL(started()), serialThread, SLOT(startReading()));
        connect(serialWorkerThread, SIGNAL(finished()), serialThread, SLOT(deleteLater()));

        connect(serialThread, SIGNAL(dataRecieve(const QByteArray&)), this, SLOT(onDataRecieve(const QByteArray&)));
        connect(serialThread, SIGNAL(connectionError()), this, SLOT(onConnectionError()));
        connect(serialThread, SIGNAL(noDataTimeout()), this, SLOT(onNoDataTimeout()));
        connect(serialThread, SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
        serialThread->initThread(serialWorkerThread);

        serialThread->moveToThread(serialWorkerThread);
        serialWorkerThread->start();
    }
}

void MindwaveReaderSerial::onConnectionError()
{
    onDisconnectionSuccess();
}

void MindwaveReaderSerial::onNoDataTimeout()
{
    onDisconnectionSuccess();
}

void MindwaveReaderSerial::onDataRecieve(const QByteArray& bytes)
{  
     emit dataRecieve(bytes);
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

//    qDebug() << "Data Write Sucessfull";
//    return;
}
