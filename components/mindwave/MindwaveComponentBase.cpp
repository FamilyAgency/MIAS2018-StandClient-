#include "MindwaveComponentBase.h"
#include <QDebug>

MindwaveComponentBase::MindwaveComponentBase(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";
    setDeviceState(DeviceState::None);
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
    setDeviceState(DeviceState::None);
    setPoorSignalLevel(200);
    setAttention(0);
    setMeditation(0);

    setConnected(false);
}

void MindwaveComponentBase::start()
{
    qDebug()<<"------------------- mindwave component start -------------------";
    mindwaveReader->start();
}

void MindwaveComponentBase::stop()
{
    qDebug()<<"------------------- mindwave component stop -------------------";
}

void MindwaveComponentBase::onSignalLevelParsed(int value)
{
    setDeviceState(DeviceState::Reading);
    setPoorSignalLevel(value);
    _poorSignalColor = value;
}

void MindwaveComponentBase::onMeditationParsed(int value)
{
    setDeviceState(DeviceState::Reading);
    setMeditation(value);
}

void MindwaveComponentBase::onAttentionParsed(int value)
{
    setDeviceState(DeviceState::Reading);
    setAttention(value);
}

void MindwaveComponentBase::onDataParsed(const MindwaveData& mindwaveData)
{
    if(mindwaveData.valid)
    {
        setMeditation(mindwaveData.meditation);
        setAttention(mindwaveData.attention);

        setPoorSignalLevel(mindwaveData.poorSignalLevel);

        setDeviceState(DeviceState::Reading);
    }
}

void MindwaveComponentBase::onScanningInfo(int signalValue, const QString& status)
{
    setMeditation(0);
    setAttention(0);
    setPoorSignalLevel(signalValue);

    if(status == "scanning")
    {
        setDeviceState(DeviceState::Scanning);
    }
    else if(status == "notscanning")
    {
        setDeviceState(DeviceState::NotScanning);
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
    _poorSignalLevel = remapPoorSignalLevel(value);
    _poorSignalColor = getPoorSignalColor(_poorSignalLevel);
    emit poorSignalLevelChanged();
}

int MindwaveComponentBase::poorSignalLevel() const
{
    return _poorSignalLevel;
}

bool MindwaveComponentBase::isSignalLevelMax() const
{
    return _poorSignalLevel == 100;
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

int MindwaveComponentBase::remapPoorSignalLevel(int signalValue)
{
    return MathTools::map<float>(signalValue, 0,  200, 100,  0);
}

QString MindwaveComponentBase::getPoorSignalColor(int value)
{
    if(value >= 66 && value <= 100)
    {
        return "#009900";
    }
    else if(value >= 30 && value <= 66)
    {
        return "#999900";
    }
    else if(value >= 0 && value <= 30)
    {
        return  "#999999";
    }

    return "#999999";
}
