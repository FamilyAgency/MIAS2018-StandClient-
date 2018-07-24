#include "MindwaveComponentTCP.h"
#include "MindwaveReaderTCP.h"
#include "MindwaveParserTCP.h"

MindwaveComponentTCP::MindwaveComponentTCP(QObject *parent) : MindwaveComponentBase(parent)
{
    mindwaveReader.reset(new MindwaveReaderTCP());
    connect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    mindwaveParser.reset(new MindwaveParserTCP());
    connect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), mindwaveParser.data(), SLOT(onDataRecieve(const QString&)));

    connect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));
    connect(mindwaveParser.data(), SIGNAL(dataParsed(const MindwaveData& data)), this, SLOT(onDataParsed(const MindwaveData& data)));
}

MindwaveComponentTCP::~MindwaveComponentTCP()
{
    disconnect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    disconnect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    disconnect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), mindwaveParser.data(), SLOT(onDataRecieve(const QString&)));
    disconnect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));
    disconnect(mindwaveParser.data(), SIGNAL(dataParsed(const MindwaveData& data)), this, SLOT(onDataParsed(const MindwaveData& data)));
}
