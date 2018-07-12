#include "ServerComponent.h"

ServerComponent::ServerComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Server";

    httpClient.reset(new HTTPClient());
    connect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    connect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

ServerComponent::~ServerComponent()
{
    disconnect(httpClient.data(), SIGNAL(httpRequestSuccess(const QString&)), this, SLOT(httpRequestSuccessHandler(const QString&)));
    disconnect(httpClient.data(), SIGNAL(httpRequestFailed(const QString&)), this, SLOT(httpRequestFailedHandler(const QString&)));
}

void ServerComponent::setQmlContext(QQmlContext* value)
{
   BaseComponent::setQmlContext(value);
   qmlContext->setContextProperty("server", this);
}

void ServerComponent::setConfig(ConfigPtr config)
{
   BaseComponent::setConfig(config);
   setServerConfig(*config->serverConfig);
   httpClient->setTimemoutInterval(_serverConfig.requestTimemoutInterval);
   httpClient->setRequestTryCount(_serverConfig.requestTryCount);
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

void ServerComponent::setServerStatus(ServerStatus serverStatus)
{
    _serverStatus = serverStatus;
    emit serverStatusChanged(_serverStatus);
}

void ServerComponent::start()
{

}

void ServerComponent::stop()
{

}

bool ServerComponent::isHealthy()
{
    return true;
}

bool ServerComponent::canRunRequest() const
{
 return _serverStatus == ServerStatus::Free;
}

void ServerComponent::fetchUser(int rfid)
{

}

void ServerComponent::logout()
{

}

void ServerComponent::httpRequestSuccessHandler(const QString& data)
{
    response.body = data;
    parse(response);
    setServerStatus(ServerStatus::Free);
    emit serverResponse(response);
}

void ServerComponent::httpRequestFailedHandler(const QString& data)
{
    setServerStatus(ServerStatus::Error);
    qDebug()<<"server error occurs";

    response.type = ResponseType::Error;
    response.errorType = ServerGlobalErrorType::NetworkError;
    response.body = data;
    emit serverGlobalError(response.errorType);
}

void ServerComponent::parse(const ServerResponse& response)
{

}
