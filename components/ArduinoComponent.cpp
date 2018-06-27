#include "ArduinoComponent.h"
#include <QSerialPortInfo>

ArduinoComponent::ArduinoComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Arduino";

    arduinoDataReader = new ArduinoDataReader();
    connect(arduinoDataReader, SIGNAL(dataReaded(const QString&)), this, SLOT(onDataReaded(const QString&)));
    connect(arduinoDataReader, SIGNAL(readError()), this, SLOT(onReadError()));
}

void ArduinoComponent::setConfig(const ArduinoConfig& config)
{
    arduinoConfig = config;
    arduinoDataReader->setConfig(config);
    emit configChanged();
}

void ArduinoComponent::start()
{
   //arduinoDataReader->start();
}

void ArduinoComponent::startReading(int modelIndex)
{
   arduinoDataReader->startReading(modelIndex);
}

QVariantList ArduinoComponent::getPortsAvailable() const
{
    return arduinoDataReader->getPortsAvailable();
}

void ArduinoComponent::onDataReaded(const QString&)
{

}

void ArduinoComponent::onReadError()
{

}

ArduinoConfig ArduinoComponent::config() const
{
    return arduinoConfig;
}

void ArduinoComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("arduino", this);
}

void ArduinoComponent::setConnected(bool value)
{
    _connected = value;
    emit connectedChanged();
}

bool ArduinoComponent::connected() const
{
    return _connected;
}

bool ArduinoComponent::isHealthy()
{
    return true;
}
