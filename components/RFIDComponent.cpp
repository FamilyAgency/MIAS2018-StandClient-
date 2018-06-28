#include "RFIDComponent.h"
#include <QSerialPortInfo>

RFIDComponent::RFIDComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "RFID";

    rfidDataReader = new UHFDataReader();
    connect(rfidDataReader, SIGNAL(dataReaded(const QString&)), this, SLOT(onDataReaded(const QString&)));
    connect(rfidDataReader, SIGNAL(readError()), this, SLOT(onReadError()));
}

void RFIDComponent::setConfig(const RFIDConfig& config)
{
    rfidConfig = config;
    rfidDataReader->setConfig(config);
    emit configChanged();
}

void RFIDComponent::start()
{
   //arduinoDataReader->start();
}

void RFIDComponent::startReading(int modelIndex)
{
   rfidDataReader->startReading(modelIndex);
}

QVariantList RFIDComponent::getPortsAvailable() const
{
    return rfidDataReader->getPortsAvailable();
}

void RFIDComponent::onDataReaded(const QString&)
{

}

void RFIDComponent::onReadError()
{

}

RFIDConfig RFIDComponent::config() const
{
    return rfidConfig;
}

void RFIDComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("rfid", this);
}

void RFIDComponent::setConnected(bool value)
{
    _connected = value;
    emit connectedChanged();
}

bool RFIDComponent::connected() const
{
    return _connected;
}

bool RFIDComponent::isHealthy()
{
    return true;
}
