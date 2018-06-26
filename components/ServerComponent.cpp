#include "ServerComponent.h"

ServerComponent::ServerComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Server";
}

void ServerComponent::setConfig(const ServerConfig& config)
{
    //TODO
    serverConfig = config;
    emit configChanged();
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
