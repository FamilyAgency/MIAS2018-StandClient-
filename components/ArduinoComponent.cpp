#include "ArduinoComponent.h"

ArduinoComponent::ArduinoComponent(QObject *parent) : BaseComponent(parent)
{

}

void ArduinoComponent::setConfig(const ArduinoConfig& config)
{
    //TODO
    arduinoConfig = config;
    emit configChanged();
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
