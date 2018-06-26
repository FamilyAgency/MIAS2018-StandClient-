#include "MindwaveComponent.h"
#include <QDebug>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include "tools/MathTools.h"

MindwaveComponent::MindwaveComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Mindwave";

    client.reset(new TCPSocketClient);
    connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    connect(client.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(client.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));
}

void MindwaveComponent::onConnectionSuccess()
{
    setConnected(true);
    qDebug()<<"MindwaveComponent : connected............";
    client->sendData(mindwaveConfig.initialCommand);
    //client->sendData(config.autchCommand);
}

void MindwaveComponent::onDisconnectionSuccess()
{
    setConnected(false);
    qDebug()<<"MindwaveComponent : disconnected............";
}

void MindwaveComponent::setConfig(const MindwaveConfig& config)
{
    //TODO
    mindwaveConfig = config;
    client->setConfig(mindwaveConfig.getTCPConfig());
    client->init();
    emit configChanged();
}

void MindwaveComponent::onItemDataRecieve(const QString& data)
{
    auto delimeter = mindwaveConfig.delimeter;

    QStringList json = data.split(delimeter);
    int count = 0;

    for(int i = 0; i < json.length(); i++)
    {
        if(json[i].indexOf("eSense") != -1)
        {
            count++;
            parse(json[i]);
            break;
        }
    }
}

void MindwaveComponent::parse(const QString& data)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();
    QJsonObject eSenseJson = jsonObj.value("eSense").toObject();
    int _poorSignalLevel = jsonObj.value("poorSignalLevel").toInt();

    const bool test = false;//true;

    _lastAttention = _attention;
    _lastMeditation = _meditation;

    if(!test)
    {
        setAttention(eSenseJson.value("attention").toInt());
        setMeditation(eSenseJson.value("meditation").toInt());
    }
    else
    {
        int min = 50;
        int max = 100;
        int RandAtten = qrand() % ((max + 1) - min) + min;
        setAttention(RandAtten);
        int  RandMed = qrand() % ((100 + 1) - 0) + 0;
        setMeditation(RandMed);
    }
    // qDebug()<<data;
    int signalValue = jsonObj.value("poorSignalLevel").toInt();
    int signalRemappedValue = MathTools::map<float>(signalValue, 0,  200, 100,  0);

    setPoorSignalLevel(signalRemappedValue);

    qDebug()<<"attention: "<<_attention <<"meditation: "<<_meditation <<"poorSignalLevel: "<<_poorSignalLevel;
}

void MindwaveComponent::setQmlContext(QQmlContext* value)
{
   BaseComponent::setQmlContext(value);
   qmlContext->setContextProperty("mind", this);
}

void MindwaveComponent::setPoorSignalLevel(int value)
{
    _poorSignalLevel = value;

    if(value >= 66 && value <= 100)
    {
        _poorSignalColor = "#009900";
    }
    else if(value >= 30 && value <= 66)
    {
        _poorSignalColor = "#999900";
    }
    else if(value >= 0 && value <= 30)
    {
        _poorSignalColor = "#999999";
    }

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


int MindwaveComponent::getAttentionDelta() const
{
    return _attention - _lastAttention;
}

int MindwaveComponent::getMeditationDelta() const
{
    return _meditation - _lastMeditation;
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
