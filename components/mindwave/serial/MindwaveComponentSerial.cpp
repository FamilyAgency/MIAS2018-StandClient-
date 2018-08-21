#include "MindwaveComponentSerial.h"
#include "MindwaveReaderSerial.h"
#include "MindwaveParserSerial.h"

MindwaveComponentSerial::MindwaveComponentSerial(QObject *parent) : MindwaveComponentBase(parent)
{
    mindwaveReader.reset(new MindwaveReaderSerial(parent));
    connect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    mindwaveParser.reset(new MindwaveParserSerial());
    connect(mindwaveReader.data(), SIGNAL(dataRecieve(const QByteArray&)), mindwaveParser.data(), SLOT(onDataRecieve(const QByteArray&)));
   // connect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));

    connect(mindwaveParser.data(), SIGNAL(signalLevelParsed(int)), this, SLOT(onSignalLevelParsed(int)));
    connect(mindwaveParser.data(), SIGNAL(meditationParsed(int)), this, SLOT(onMeditationParsed(int)));
    connect(mindwaveParser.data(), SIGNAL(attentionParsed(int)), this, SLOT(onAttentionParsed(int)));
}

MindwaveComponentSerial::~MindwaveComponentSerial()
{
    disconnect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    disconnect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    disconnect(mindwaveReader.data(), SIGNAL(dataRecieve(const QByteArray&)), mindwaveParser.data(), SLOT(onDataRecieve(const QByteArray&)));
   // disconnect(mindwaveParser.data(), SIGNAL(scanningInfo(int , const QString&)), this, SLOT(onScanningInfo(int , const QString&)));

    disconnect(mindwaveParser.data(), SIGNAL(signalLevelParsed(int)), this, SLOT(onSignalLevelParsed(int)));
    disconnect(mindwaveParser.data(), SIGNAL(meditationParsed(int)), this, SLOT(onMeditationParsed(int)));
    disconnect(mindwaveParser.data(), SIGNAL(attentionParsed(int)), this, SLOT(onAttentionParsed(int)));
}
