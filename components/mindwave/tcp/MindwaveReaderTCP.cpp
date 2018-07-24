#include "MindwaveReaderTCP.h"

MindwaveReaderTCP::MindwaveReaderTCP(QObject *parent) : MindwaveReaderBase(parent)
{
    client.reset(new TCPSocketClient);
    connect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    connect(client.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    connect(client.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));
}

MindwaveReaderTCP::~MindwaveReaderTCP()
{
    disconnect(client.data(), SIGNAL(socketDataRecieve(const QString&)), this, SLOT(onItemDataRecieve(const QString&)));
    disconnect(client.data(), SIGNAL(connectionSuccess()), this, SLOT(onConnectionSuccess()));
    disconnect(client.data(), SIGNAL(disconnectionSuccess()), this, SLOT(onDisconnectionSuccess()));
}

void MindwaveReaderTCP::setConfig(const MindwaveConfig& config)
{
    MindwaveReaderBase::setConfig(config);
    client->setConfig(mindwaveConfig.getTCPConfig());
}

void MindwaveReaderTCP::start()
{
     client->init();
}

void MindwaveReaderTCP::onConnectionSuccess()
{
    MindwaveReaderBase::onConnectionSuccess();
    client->sendData(mindwaveConfig.initialCommand);
}
