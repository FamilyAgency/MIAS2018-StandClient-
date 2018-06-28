#include "MindwaveComponent.h"
#include <QDebug>

MindwaveComponent::MindwaveComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";

    mindwaveReader = new MindwaveReader();
    connect(mindwaveReader, SIGNAL(dataRecieve(const QString&)), this, SLOT(onDataRecieve(const QString&)));
    connect(mindwaveReader, SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(mindwaveReader, SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    mindwaveParser = new MindwaveParser();
}

void MindwaveComponent::onConnectionSuccess()
{
    setConnected(true);
}

void MindwaveComponent::onDisconnectionSuccess()
{
    setConnected(false);
}

void MindwaveComponent::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
    mindwaveReader->setConfig(mindwaveConfig);
    mindwaveParser->setConfig(mindwaveConfig);
    emit configChanged();
}

void MindwaveComponent::start()
{
    mindwaveReader->start();
}

void MindwaveComponent::onDataRecieve(const QString& data)
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

void MindwaveComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("mind", this);
}

void MindwaveComponent::setPoorSignalLevel(int value)
{
    _poorSignalLevel = value;
    emit poorSignalLevelChanged();
}

int MindwaveComponent::poorSignalLevel() const
{
    return _poorSignalLevel;
}

void MindwaveComponent::setAttention(int value)
{
    _attention = value;
    emit attentionChanged();
}

int MindwaveComponent::attention() const
{
    return _attention;
}

void MindwaveComponent::setMeditation(int value)
{
    _meditation = value;
    emit meditationChanged();
}

int MindwaveComponent::meditation() const
{
    return _meditation;
}

QString MindwaveComponent::poorSignalColor() const
{
    return _poorSignalColor;
}

MindwaveConfig MindwaveComponent::config() const
{
    return mindwaveConfig;
}

void MindwaveComponent::setConnected(bool value)
{
    _connected = value;
    emit connectedChanged();
}

bool MindwaveComponent::connected() const
{
    return _connected;
}

bool MindwaveComponent::isHealthy()
{
    return true;
}
