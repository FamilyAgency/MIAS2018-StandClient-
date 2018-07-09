#include "ServerComponent.h"

ServerComponent::ServerComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Server";
}

void ServerComponent::setConfig(ConfigPtr config)
{

//    serverConfig = config;
//    emit configChanged();
}

void ServerComponent::start()
{

}

void ServerComponent::stop()
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

void ServerComponent::fetchUser(int deviceId, int rfid)
{

}
