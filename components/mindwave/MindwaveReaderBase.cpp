#include "MindwaveReaderBase.h"

MindwaveReaderBase::MindwaveReaderBase(QObject *parent) : QObject(parent)
{

}

MindwaveReaderBase::~MindwaveReaderBase()
{

}

void MindwaveReaderBase::onConnectionSuccess()
{
    qDebug()<<"MindwaveReader : connected............";
    setConnected(true);
    emit connectionSuccess();
}

void MindwaveReaderBase::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
}

void MindwaveReaderBase::start()
{

}

void MindwaveReaderBase::onDisconnectionSuccess()
{
    qDebug()<<"MindwaveReader : disconnected............";
    setConnected(false);    
    emit disconnectionSuccess();
}

void MindwaveReaderBase::onItemDataRecieve(const QString& data)
{
    emit dataRecieve(data);
}

 void MindwaveReaderBase::setConnected(bool value)
 {
     _connected = value;
 }
