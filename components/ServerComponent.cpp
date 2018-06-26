#include "ServerComponent.h"

ServerComponent::ServerComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Server";
}

void ServerComponent::setConfig(const ServerConfig& config)
{   
    serverConfig = config;
    emit configChanged();
}

void ServerComponent::start()
{

}

ServerConfig ServerComponent::config() const
{
    return serverConfig;
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
