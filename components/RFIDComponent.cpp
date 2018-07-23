#include "RFIDComponent.h"
#include <QSerialPortInfo>

RFIDComponent::RFIDComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Rfid";

    rfidDataReader.reset(new BaseRFIDDataReader());
    connect(rfidDataReader.data(), SIGNAL(dataReaded(const QString&)), this, SLOT(onDataReaded(const QString&)));
    connect(rfidDataReader.data(), SIGNAL(readError()), this, SLOT(onReadError()));
}

RFIDComponent::~RFIDComponent()
{
    disconnect(rfidDataReader.data(), SIGNAL(dataReaded(const QString&)), this, SLOT(onDataReaded(const QString&)));
    disconnect(rfidDataReader.data(), SIGNAL(readError()), this, SLOT(onReadError()));
}

void RFIDComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("rfid", this);
}

void RFIDComponent::setConfig(ConfigPtr config)
{
    BaseComponent::setConfig(config);
    setRfidConfig(*config->rfidConfig);
}

void RFIDComponent::setRfidConfig(const RFIDConfig& value)
{
    _rfidConfig = value;
    emit rfidConfigChanged();
}

RFIDConfig RFIDComponent::rfidConfig() const
{
    return _rfidConfig;
}

void RFIDComponent::start()
{
   //arduinoDataReader->start();
}

void RFIDComponent::stop()
{

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
