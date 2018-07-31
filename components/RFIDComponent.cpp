#include "RFIDComponent.h"
#include "rfid/ACR122CardHandler.h"
#include <QSerialPortInfo>

RFIDComponent::RFIDComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Rfid";
}

RFIDComponent::~RFIDComponent()
{

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

}

void RFIDComponent::stop()
{

}

void RFIDComponent::startReadingId()
{

}

void RFIDComponent::startReadingAllData()
{

}

void RFIDComponent::startReading()
{

}

void RFIDComponent::startWriting(const QString& data)
{

}

void RFIDComponent::stopAll()
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

void RFIDComponent::setCardReaderState(CardReaderState state)
{
    cardReaderState = state;
    emit cardReaderStateChanged(state);
}

