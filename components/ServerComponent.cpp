#include "ServerComponent.h"

ServerComponent::ServerComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Server";
}

ServerComponent::~ServerComponent()
{

}

void ServerComponent::setConfig(ConfigPtr config)
{
   BaseComponent::setConfig(config);
   setServerConfig(*config->serverConfig);
}

ServerConfig ServerComponent::serverConfig() const
{
    return _serverConfig;
}

void ServerComponent::setServerConfig(const ServerConfig& value)
{
    _serverConfig = value;
    emit serverConfigChanged();
}

void ServerComponent::start()
{

}

void ServerComponent::stop()
{

}

void ServerComponent::setQmlContext(QQmlContext* value)
{
   BaseComponent::setQmlContext(value);
   qmlContext->setContextProperty("server", this);
}

bool ServerComponent::isHealthy()
{
    return true;
}

void ServerComponent::fetchUser(int deviceId, int rfid)
{

}
