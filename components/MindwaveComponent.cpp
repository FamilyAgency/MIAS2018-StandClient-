#include "MindwaveComponent.h"
#include <QDebug>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include "tools/MathTools.h"

MindwaveComponent::MindwaveComponent(QObject *parent) : QObject(parent)
{
    client.reset(new TCPSocketClient);
    connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    connect(client.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(client.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));

}

void MindwaveComponent::onConnectionSuccess()
{
    qDebug()<<"MindwaveComponent : connected";
    client->sendData("{\"enableRawOutput\": true, \"format\": \"Json\"}\\r");

    senderTimer = new QTimer(this);
    senderTimer->setSingleShot(true);
    senderTimer->setInterval(2000);
    connect(senderTimer, SIGNAL(timeout()), this, SLOT(senderTimerHandler()));
    senderTimer->start();
}

void MindwaveComponent::senderTimerHandler()
{
    client->sendData("{\"appName\":\"BrainwaveShooters\",\"appKey\":\"0054141b4b4c567c558d3a76cb8d715cbde03096\"}\\r");
   // sendData("{""getAppNames"":null}\\r");
}

void MindwaveComponent::onDisconnectionSuccess()
{
    qDebug()<<"MindwaveComponent : disconnected............";
}

void MindwaveComponent::setConfig(const MindwaveConfig& config)
{
    client->setConfig(config.tcpConfig);
    client->init();
}

void MindwaveComponent::onItemDataRecieve(const QString& data)
{
    auto delimeter = mindwaveConfig.tcpConfig.delimeter;

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

int MindwaveComponent::attention() const
{
    return _attention;
}

int MindwaveComponent::meditation() const
{
    return _meditation;
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

void MindwaveComponent::setMeditation(int value)
{
    _meditation = value;
    emit meditationChanged();
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

QString MindwaveComponent::poorSignalColor() const
{
    return _poorSignalColor;
}

int MindwaveComponent::getAttentionDelta() const
{
    return _attention - _lastAttention;
}

int MindwaveComponent::getMeditationDelta() const
{
    return _meditation - _lastMeditation;
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
