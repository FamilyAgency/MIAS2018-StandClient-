#include "ServerRemoteComponent.h"
#include <QUrlQuery>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

ServerRemoteComponent::ServerRemoteComponent(QObject *parent) : ServerComponent(parent)
{
    name = "Server Remote";
}

void ServerRemoteComponent::configRequest(int deviceId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }
    response.clear();
    response.type = ResponseType::ConfigRequest;
    setServerStatus(ServerStatus::Busy);
    QString fullRequest = serverConfig().url + "/config/" + QString::number(deviceId);
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::updatesRequest(int deviceId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::UpdatesRequest;
    setServerStatus(ServerStatus::Busy);
    QString fullRequest = serverConfig().url + "/config/" + QString::number(deviceId) + "/updates";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::healthLogRequest(int deviceId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    //    response.clear();
    //    response.type = ResponseType::HealthLogRequest;
    //    setServerStatus(ServerStatus::Busy);
}

void ServerRemoteComponent::allUsersRequest()
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::AllUsersRequest;
    setServerStatus(ServerStatus::Busy);
    QString fullRequest = serverConfig().url + "/users";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::createUserRequest(const QString& name,
                                              const QString& surname,
                                              const QString& email,
                                              const QString& phone,
                                              bool test)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::CreateUserRequest;
    setServerStatus(ServerStatus::Busy);

    QNetworkRequest request(serverConfig().url + "/users/register");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("name", name);
    query.addQueryItem("surname", surname);
    query.addQueryItem("email", email);
    query.addQueryItem("phone", phone);
    query.addQueryItem("test", test ? "1" : "0");

    qDebug()<<"fullRequest "<<serverConfig().url + "/users/register";
    httpClient->runPostRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
}

void ServerRemoteComponent::createUserRequest(bool isTestUser)
{
    createUserRequest("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                      "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                      "яндекс@почта.рф",
                      "+79067704595",
                      isTestUser ? "1" : "0");

//    createUserRequest("Вика",
//                      "Журавлева",
//                      "vika@gmail.com",
//                      "+89151546522",
//                      isTestUser ? "1" : "0");
}

void ServerRemoteComponent::searchUserRequest(const QString& email, const QString& phone)
{
    if(email.isEmpty() && phone.isEmpty())
    {
        return;
    }

    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::SearchUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/search/?";

    QUrlQuery query;
    if(!email.isEmpty())
    {
        query.addQueryItem("email", email);
    }
    else if(!phone.isEmpty())
    {
        query.addQueryItem("phone", phone);
    }
    else
    {
        // empty fields
        return;
    }
    fullRequest.append(query.toString(QUrl::FullyEncoded).toUtf8());
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::searchUserByIdRequest(int userId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::SearchUserByIdRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId);
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::deleteAllTestUsersRequest()
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::DeleteAllTestUsersRequest;
    setServerStatus(ServerStatus::Busy);

    QNetworkRequest request(serverConfig().url + "/users/0");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    qDebug()<<"fullRequest ";//<<fullRequest;
    httpClient->runDeleteRequest(request);
}

void ServerRemoteComponent::verifyUserRequest(int userId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::VerifyUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/verify";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::confirmUserRequest(int userId, int code)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::ConfirmUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/confirm";
    QNetworkRequest request(fullRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("code", QString::number(code));
    httpClient->runPostRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
}

void ServerRemoteComponent::confirmPrizeRequest(int userId, int prizeid)
{
//    if(!canRunRequest())
//    {
//        qDebug()<<"wait for server please";
//        return;
//    }

//    response.clear();
//    response.type = ResponseType::ConfirmPrizeRequest;
//    setServerStatus(ServerStatus::Busy);
}

void ServerRemoteComponent::parse(const ServerResponse& response)
{
    qDebug() << "ServerRemoteComponent " << response.body;
    emit serverLogged(response.body);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.body.toUtf8());
    QJsonObject responeJson   = jsonDoc.object();

    QString status = responeJson["status"].toString();
    int code = responeJson["code"].toInt();

    qDebug() << "status: " << status;
    qDebug() << "code: " << code;

    if(status != "success" || code != 200)
    {
        handleRequestError(response);
        return;
    }

    if(response.type == ResponseType::CreateUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();       
        createBaseUserInfo(dataJson);
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::ConfirmUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();        
        createBaseUserInfo(dataJson);
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::VerifyUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();        
        createBaseUserInfo(dataJson);
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::SearchUserRequest)
    {
        QJsonArray dataArrayJson = responeJson["data"].toArray();

        if(dataArrayJson.size() > 0 )
        {
            QJsonObject dataJson = dataArrayJson[0].toObject();           
            createBaseUserInfo(dataJson);
            emit serverRequestSuccess(response.type);
        }
        else
        {
            emit userNotFound();
            qDebug()<<"===== nobody was found =====";
        }
    }
    else if(response.type == ResponseType::SearchUserByIdRequest)
    {
        qDebug()<<"===== SearchUserRequest =====";
        QJsonObject dataJson = responeJson["data"].toObject();
        if(!dataJson.empty())
        {
            createBaseUserInfo(dataJson);
            emit serverRequestSuccess(response.type);
        }
        else
        {
            emit userNotFound();
            qDebug()<<"===== nobody was found =====";
        }
    }
}

void ServerRemoteComponent::handleRequestError(const ServerResponse& response)
{
    qDebug() << "server error: " << (int)response.type;
    serverRequestError(response.type);
}

void ServerRemoteComponent::setBaseUserInfo(const BaseUserInfo& baseUserInfo)
{
    _baseUserInfo = baseUserInfo;
    emit baseUserInfoChanged();
}

BaseUserInfo ServerRemoteComponent::baseUserInfo() const
{
    return _baseUserInfo;
}

void ServerRemoteComponent::clearBaseUserInfo()
{
    _baseUserInfo.clear();
    emit baseUserInfoChanged();
}

void ServerRemoteComponent::createBaseUserInfo(const QJsonObject& object)
{
    BaseUserInfo baseUserInfo;
    baseUserInfo.id = object["id"].toInt();
    baseUserInfo.name = object["name"].toString();
    baseUserInfo.surname = object["surname"].toString();
    baseUserInfo.email = object["email"].toString();
    baseUserInfo.phone = object["phone"].toString();
    baseUserInfo.confirmed = object["confirmed"].toInt();
    baseUserInfo.test = object["test"].toInt();
    baseUserInfo.print();
    setBaseUserInfo(baseUserInfo);
}

void ServerRemoteComponent::simulateServerError()
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::VerifyUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url;
    httpClient->runGetRequest(fullRequest);
   // httpRequestFailedHandler("Error: Simulate Server Error");
}

