#include "MindwaveComponentBase.h"
#include <QDebug>

MindwaveComponentBase::MindwaveComponentBase(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";

    timeoutTimer = new QTimer(this);
    connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(onTimeoutHandle()));

    setDeviceState(DeviceState::None);
}

MindwaveComponentBase::~MindwaveComponentBase()
{
    if(timeoutTimer)
    {
        disconnect(timeoutTimer, SIGNAL(timeout()), this, SLOT(onTimeoutHandle()));
        delete timeoutTimer;
    }
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
    setDeviceState(DeviceState::None);
    setConnected(false);
}

void MindwaveComponentBase::start()
{
    timeoutTimer->start(_mindwaveConfig.timeoutMills);
    mindwaveReader->start();
}

void MindwaveComponentBase::stop()
{
    timeoutTimer->stop();
}

void MindwaveComponentBase::onSignalLevelParsed(int value)
{
    setPoorSignalLevel(value);
    _poorSignalColor = mindwaveParser->getPoorSignalColor(value);

    qDebug()<<"onSignalLevelParsed "<<value;
    setDeviceState(DeviceState::Reading);
    timeoutTimer->start(_mindwaveConfig.timeoutMills);

    setPoorSignalLevel(value);
}

void MindwaveComponentBase::onMeditationParsed(int value)
{
    qDebug()<<"onMeditationParsed "<<value;
    setDeviceState(DeviceState::Reading);
    timeoutTimer->start(_mindwaveConfig.timeoutMills);

     setMeditation(value);
}

void MindwaveComponentBase::onAttentionParsed(int value)
{
    qDebug()<<"onAttentionParsed "<<value;
    setDeviceState(DeviceState::Reading);
    timeoutTimer->start(_mindwaveConfig.timeoutMills);

      setAttention(value);
}

void MindwaveComponentBase::onDataParsed(const MindwaveData& mindwaveData)
{
    if(mindwaveData.valid)
    {
        setMeditation(mindwaveData.meditation);
        setAttention(mindwaveData.attention);

        _poorSignalColor = mindwaveParser->getPoorSignalColor(mindwaveData.poorSignalLevel);
        setPoorSignalLevel(mindwaveData.poorSignalLevel);

        setDeviceState(DeviceState::Reading);
        timeoutTimer->start(_mindwaveConfig.timeoutMills);
    }
}

void MindwaveComponentBase::onScanningInfo(int signalValue, const QString& status)
{
    setMeditation(0);
    setAttention(0);
    setPoorSignalLevel(signalValue);
    _poorSignalColor = mindwaveParser->getPoorSignalColor(signalValue);

    timeoutTimer->stop();

    if(status == "scanning")
    {
        setDeviceState(DeviceState::Scanning);
    }
    else if(status == "notscanning")
    {
        setDeviceState(DeviceState::NotScanning);
    }
}

void MindwaveComponentBase::onTimeoutHandle()
{
    if(deviceState == DeviceState::Reading)
    {
        qDebug()<<"==================onTimeoutHandle==================";
        setDeviceState(DeviceState::None);
    }
}

void MindwaveComponentBase::setDeviceState(DeviceState value)
{
    deviceState = value;
    emit deviceStateChanged(deviceState);
}

MindwaveComponentBase::DeviceState MindwaveComponentBase::getDeviceState() const
{
    return deviceState;
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
