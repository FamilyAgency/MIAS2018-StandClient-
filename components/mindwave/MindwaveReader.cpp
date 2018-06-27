#include "MindwaveReader.h"

MindwaveReader::MindwaveReader(QObject *parent) : QObject(parent)
{
    client.reset(new TCPSocketClient);
    connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    connect(client.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(client.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));
}

void MindwaveReader::onConnectionSuccess()
{
    setConnected(true);
    qDebug()<<"MindwaveReader : connected............";
    client->sendData(mindwaveConfig.initialCommand);
    //client->sendData(config.autchCommand);

    emit connectionSuccess();
}

void MindwaveReader::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
    client->setConfig(mindwaveConfig.getTCPConfig());
}

void MindwaveReader::start()
{
     client->init();
}

void MindwaveReader::onDisconnectionSuccess()
{
    setConnected(false);
    qDebug()<<"MindwaveReader : disconnected............";
    emit disconnectionSuccess();
}

void MindwaveReader::onItemDataRecieve(const QString& data)
{
    emit onDataRecieve(data);
}

 void MindwaveReader::setConnected(bool value)
 {
     _connected = value;
 }
