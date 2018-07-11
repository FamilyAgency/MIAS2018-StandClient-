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
    qDebug()<<"fullRequest "<<fullRequest;
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
    qDebug()<<"fullRequest "<<fullRequest;
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::healthLogRequest(int deviceId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::HealthLogRequest;
    setServerStatus(ServerStatus::Busy);
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
    qDebug()<<"fullRequest "<<fullRequest;
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::createUserRequest(bool isTestUser)
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
    QString name = "Юрий";
    query.addQueryItem("name", "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
    query.addQueryItem("surname", "абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    query.addQueryItem("email", "яндекс@почта.рф");
    query.addQueryItem("phone", "89067704595");
    query.addQueryItem("test", isTestUser ? "1" : "0");

//    query.addQueryItem("name", "Вика");
//    query.addQueryItem("surname", "Журавлева");
//    query.addQueryItem("email", "vika@gmail.com");
//    query.addQueryItem("phone", "89151546522");
//    query.addQueryItem("test", isTestUser ? "1" : "0");

    httpClient->runPostRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
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
    fullRequest += query.toString();

    qDebug()<<"fullRequest "<<fullRequest;
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

void ServerRemoteComponent::verifyUserRequest(int id)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::VerifyUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(id) + "/verify";
    qDebug()<<"fullRequest "<<fullRequest;
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::confirmUserRequest(int id, int code)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::ConfirmUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(id) + "/confirm";
    QNetworkRequest request(fullRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("code", QString::number(code));

    httpClient->runPostRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
}

void ServerRemoteComponent::parse(const ServerResponse& response)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.body.toUtf8());
    QJsonObject responeJson   = jsonDoc.object();

    QString status = responeJson["status"].toString();
    int code = responeJson["code"].toInt();

    if(status != "success" || code != 200)
    {
        qDebug()<<"Huston we have a problems. level 1";
        return;
    }

    QJsonObject dataJson = responeJson["data"].toObject();

    //qDebug()<<dataJson.find("status");
   // return;
    //dataJson["status"].

    status = dataJson["status"].toString();
    code = dataJson["code"].toInt();

//    if(status != "success" || code != 200)
//    {
//        qDebug()<<"Huston we have a problems. level 2";
//        return;
//    }

    if(response.type == ResponseType::CreateUserRequest)
    {
        int id = dataJson["id"].toInt();
        auto name = dataJson["name"];
        QString surname = dataJson["surname"].toString();
        QString email = dataJson["email"].toString();
        QString phone = dataJson["phone"].toString();

        qDebug()<<" ===== Server :: User Created :: ";
        qDebug()<<"id = "<<id;
        qDebug()<<"name = "<<name;
        qDebug()<<"surname = "<<surname;
        qDebug()<<"email = "<<email;
        qDebug()<<"phone = "<<phone;
        qDebug()<<"====================";
    }
    else if(response.type == ResponseType::ConfirmUserRequest)
    {

    }
    else if(response.type == ResponseType::VerifyUserRequest)
    {

    }
    else if(response.type == ResponseType::SearchUserRequest)
    {

    }
    else if(response.type == ResponseType::GetUserDataRequest)
    {

    }
}

