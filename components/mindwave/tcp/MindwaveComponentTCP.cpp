#include "MindwaveComponentTCP.h"
#include "MindwaveReaderTCP.h"
#include "MindwaveParserTCP.h"

MindwaveComponentTCP::MindwaveComponentTCP(QObject *parent) : MindwaveComponentBase(parent)
{
    mindwaveReader.reset(new MindwaveReaderTCP());
    connect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), this, SLOT(onDataRecieve(const QString&)));
    connect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    mindwaveParser.reset(new MindwaveParserTCP());
    connect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));
}

MindwaveComponentTCP::~MindwaveComponentTCP()
{
    disconnect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), this, SLOT(onDataRecieve(const QString&)));
    disconnect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    disconnect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    disconnect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));
}

//MindwaveComponentTCP::onScanningInfo(int , const QString&)
//{

//}

//void MindwaveComponentTCP::onDataRecieve(const QString& data)
//{

//}
