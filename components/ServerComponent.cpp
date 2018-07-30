#include "ServerComponent.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

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
    ExternalSystemComponent::setQmlContext(value);
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

bool ServerComponent::canRunRequest() const
{
    return _serverStatus == ServerStatus::Free;
}

void ServerComponent::httpRequestSuccessHandler(const QString& data)
{
    setServerStatus(ServerStatus::Free);

    response.body = data;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.body.toUtf8());
    QJsonObject responeJson   = jsonDoc.object();

    response.status = responeJson["status"].toString();
    response.code = responeJson["code"].toInt();

    parse(response);
    emit serverResponse(response);
}

void ServerComponent::httpRequestFailedHandler(const QString& data)
{
    qDebug()<<"server error occurs";
    setServerStatus(ServerStatus::Error);
    response.body = data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.body.toUtf8());
    QJsonObject responeJson   = jsonDoc.object();
    response.status = responeJson["status"].toString();
    response.code = responeJson["code"].toInt();
    response.type = ResponseType::Error;
    response.errorType = ServerGlobalErrorType::NetworkError;

    emit serverGlobalError(response.errorType);
}

//void ServerComponent::parse(const ServerResponse& response)
//{
//    //implementation needed, inherited classes
//}
