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
        serialThread->setNoDataTimeoutMills(6000);//mindwaveConfig.timeoutMills);
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


