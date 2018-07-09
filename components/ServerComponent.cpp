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

void ServerComponent::fetchUser(int rfid)
{

}

void ServerComponent::httpRequestSuccessHandler(const QString& data)
{
    setServerStatus(ServerStatus::Free);

    ServerResponse response;
    response.type = ResponseType::UserFetched;
    response.body = data;
    emit serverResponse(response);
}

void ServerComponent::httpRequestFailedHandler(const QString& data)
{
    setServerStatus(ServerStatus::Free);
    qDebug()<<"server error occurs";

    ServerResponse response;
    response.type = ResponseType::Error;
    response.errorType = ServerErrorType::NetworkError;
    response.body = data;
    emit serverError();
    emit serverResponse(response);
}
