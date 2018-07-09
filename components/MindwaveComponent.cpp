#include "MindwaveComponent.h"
#include <QDebug>

MindwaveComponent::MindwaveComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";

    mindwaveReader.reset(new MindwaveReader());
    connect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), this, SLOT(onDataRecieve(const QString&)));
    connect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

    mindwaveParser.reset(new MindwaveParser());
}

MindwaveComponent::~MindwaveComponent()
{
    disconnect(mindwaveReader.data(), SIGNAL(dataRecieve(const QString&)), this, SLOT(onDataRecieve(const QString&)));
    disconnect(mindwaveReader.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    disconnect(mindwaveReader.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));
}

void MindwaveComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("mind", this);
}

void MindwaveComponent::setConfig(ConfigPtr config)
{
    BaseComponent::setConfig(config);

    setMindwaveConfig(*config->mindwaveConfig);

    mindwaveReader->setConfig(_mindwaveConfig);
    mindwaveParser->setConfig(_mindwaveConfig);
}

void MindwaveComponent::setMindwaveConfig(const MindwaveConfig& value)
{
    _mindwaveConfig = value;
    emit mindwaveConfigChanged();
}

MindwaveConfig MindwaveComponent::mindwaveConfig() const
{
    return _mindwaveConfig;
}

void MindwaveComponent::onConnectionSuccess()
{
    setConnected(true);
}

void MindwaveComponent::onDisconnectionSuccess()
{
    setConnected(false);
}

void MindwaveComponent::start()
{
    mindwaveReader->start();
}

void MindwaveComponent::stop()
{

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
