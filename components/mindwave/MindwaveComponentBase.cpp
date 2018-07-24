#include "MindwaveComponentBase.h"
#include <QDebug>

MindwaveComponentBase::MindwaveComponentBase(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";
}

MindwaveComponentBase::~MindwaveComponentBase()
{

}

void MindwaveComponentBase::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("mind", this);
}

void MindwaveComponentBase::setConfig(ConfigPtr config)
{
    BaseComponent::setConfig(config);

    setMindwaveConfig(*config->mindwaveConfig);
    mindwaveReader->setConfig(_mindwaveConfig);
    mindwaveParser->setConfig(_mindwaveConfig);
}

void MindwaveComponentBase::setMindwaveConfig(const MindwaveConfig& value)
{
    _mindwaveConfig = value;
    emit mindwaveConfigChanged();
}

MindwaveConfig MindwaveComponentBase::mindwaveConfig() const
{
    return _mindwaveConfig;
}

void MindwaveComponentBase::onConnectionSuccess()
{
    setConnected(true);
}

void MindwaveComponentBase::onDisconnectionSuccess()
{
    setConnected(false);
}

void MindwaveComponentBase::start()
{
    mindwaveReader->start();
}

void MindwaveComponentBase::stop()
{

}

void MindwaveComponentBase::onDataRecieve(const QString& data)
{
    MindwaveData mindwaveData = mindwaveParser->parse(data);

    if(mindwaveData.valid)
    {
        setMeditation(mindwaveData.meditation);
        setAttention(mindwaveData.attention);

        _poorSignalColor = mindwaveData.poorSignalColor;
        setPoorSignalLevel(mindwaveData.poorSignalLevel);
    }
}

void MindwaveComponentBase::onScanningInfo(int signalValue, const QString& status)
{
    setMeditation(0);
    setAttention(0);
    setPoorSignalLevel(signalValue);
  //  _poorSignalColor = mindwaveData.poorSignalColor;
}

void MindwaveComponentBase::setPoorSignalLevel(int value)
{
    _poorSignalLevel = value;
    emit poorSignalLevelChanged();
}

int MindwaveComponentBase::poorSignalLevel() const
{
    return _poorSignalLevel;
}

void MindwaveComponentBase::setAttention(int value)
{
    _attention = value;
    emit attentionChanged();
}

int MindwaveComponentBase::attention() const
{
    return _attention;
}

void MindwaveComponentBase::setMeditation(int value)
{
    _meditation = value;
    emit meditationChanged();
}

int MindwaveComponentBase::meditation() const
{
    return _meditation;
}

QString MindwaveComponentBase::poorSignalColor() const
{
    return _poorSignalColor;
}

void MindwaveComponentBase::setConnected(bool value)
{
    _connected = value;
    emit connectedChanged();
}

bool MindwaveComponentBase::connected() const
{
    return _connected;
}

bool MindwaveComponentBase::isHealthy()
{
    return true;
}
