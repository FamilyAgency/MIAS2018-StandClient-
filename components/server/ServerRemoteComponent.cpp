#include "ServerRemoteComponent.h"
#include <QUrlQuery>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

ServerRemoteComponent::ServerRemoteComponent(QObject *parent) : ServerComponent(parent)
{
    name = "Server Remote";
}

void ServerRemoteComponent::logout()
{

}

void ServerRemoteComponent::start()
{

}

void ServerRemoteComponent::stop()
{

}

void ServerRemoteComponent::commonRequest(ResponseType type, const QNetworkRequest& request, HTTPMethod httpMethod, const QByteArray& data)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = type;
    setServerStatus(ServerStatus::Busy);

    switch(httpMethod)
    {
    case HTTPMethod::GET:
        httpClient->runGetRequest(request);
        break;

    case HTTPMethod::POST:
        httpClient->runPostRequest(request, data);
        break;

    case HTTPMethod::PUT:
        httpClient->runPutRequest(request, data);
        break;

    case HTTPMethod::DELETE:
        httpClient->runDeleteRequest(request);
        break;
    }
}

void ServerRemoteComponent::configRequest(int deviceId)
{    
    QNetworkRequest request(serverConfig().url + "/config/" + QString::number(deviceId));
    commonRequest(ResponseType::ConfigRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::updatesRequest(int deviceId)
{
    QNetworkRequest request(serverConfig().url + "/config/" + QString::number(deviceId) + "/updates");
    commonRequest(ResponseType::UpdatesRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::healthLogRequest(int deviceId)
{

}

void ServerRemoteComponent::allUsersRequest()
{
    QNetworkRequest request(serverConfig().url + "/users");
    commonRequest(ResponseType::AllUsersRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::createUserRequest(const QString& name,
                                              const QString& surname,
                                              const QString& email,
                                              const QString& phone,
                                              const QString& gender)
{

    QNetworkRequest request(serverConfig().url + "/users/register");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("name", name);
    query.addQueryItem("surname", surname);
    query.addQueryItem("email", email);
    query.addQueryItem("phone", phone);
    query.addQueryItem("test", _serverConfig.serverAPI.testUser);
    query.addQueryItem("gender", gender);

    qDebug()<<"fullRequest "<<serverConfig().url + "/users/register";
    qDebug()<<"testUser "<<_serverConfig.serverAPI.testUser;
    qDebug()<<"name "<<name;
    qDebug()<<"surname "<<surname;
    qDebug()<<"email "<<email;
    qDebug()<<"phone "<<phone;

    auto data = query.toString(QUrl::FullyEncoded).toUtf8();

    commonRequest(ResponseType::CreateUserRequest, request, HTTPMethod::POST, data);
}

void ServerRemoteComponent::createUserRequest()
{
    createUserRequest("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                      "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                      "яндекс@почта.рф",
                      "+79067704595");
}

void ServerRemoteComponent::searchUserRequest(const QString& email, const QString& phone)
{
    if(email.isEmpty() && phone.isEmpty())
    {
        return;
    }

    QString URL( serverConfig().url + "/users/search/?");

    QUrlQuery query;
    if(!email.isEmpty())
    {
        query.addQueryItem("email", email);
    }
    else if(!phone.isEmpty())
    {
        query.addQueryItem("phone", phone);
    }

    URL.append(query.toString(QUrl::FullyEncoded).toUtf8());
    QNetworkRequest request(URL);
    commonRequest(ResponseType::SearchUserRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::searchUserByIdRequest(int userId)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId));
    commonRequest(ResponseType::SearchUserByIdRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::deleteAllTestUsersRequest()
{
    QNetworkRequest request(serverConfig().url + "/users/0");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    commonRequest(ResponseType::DeleteAllTestUsersRequest, request, HTTPMethod::DELETE);
}

void ServerRemoteComponent::verifyUserRequest(int userId)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/verify");
    commonRequest(ResponseType::VerifyUserRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::confirmUserRequest(int userId, int code)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/confirm");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("code", QString::number(code));

    auto data =  query.toString(QUrl::FullyEncoded).toUtf8();
    commonRequest(ResponseType::ConfirmUserRequest, request, HTTPMethod::POST, data);
}

void ServerRemoteComponent::confirmPrizeRequest(int userId, int prizeid)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/prizes/" + QString::number(prizeid));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("status", QString::number(1));
    auto data = query.toString(QUrl::FullyEncoded).toUtf8();
    qDebug()<<"prizes  "<<serverConfig().url + "/users/" + QString::number(userId) + "/prizes/" + QString::number(prizeid);
    commonRequest(ResponseType::ConfirmPrizeRequest, request, HTTPMethod::PUT, data);
}

void ServerRemoteComponent::startGameRequest(int userId)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/games/start");
    commonRequest(ResponseType::StartGameRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::updateGameRequest(int userId)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/games/update");
    commonRequest(ResponseType::UpdateGameRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::finishGameRequest(int userId)
{
    QNetworkRequest request(serverConfig().url + "/users/" + QString::number(userId) + "/games/finish");
    commonRequest(ResponseType::FinishGameRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::getDealersRequest()
{
    QNetworkRequest request(serverConfig().url + "/dealers");
    commonRequest(ResponseType::GetDealersRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponent::testDriveRequest(int userId, int dealerId)
{
    QNetworkRequest request(serverConfig().url + "/testdrive");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    query.addQueryItem("user_id", QString::number(userId));
    query.addQueryItem("dealer_id", QString::number(dealerId));

    qDebug()<<"fullRequest "<<serverConfig().url + "/testdrive";
    qDebug()<<"user_id "<<userId;
    qDebug()<<"dealer_id "<<dealerId;

    auto data = query.toString(QUrl::FullyEncoded).toUtf8();
    commonRequest(ResponseType::TestDriveRequest, request, HTTPMethod::POST, data);
}


//======================== PARSING ========================//
//=========================================================//
//=========================================================//

void ServerRemoteComponent::parse(const ServerResponse& response)
{
    qDebug() << "ServerRemoteComponent " << response.body;
    emit serverLogged(response.body);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.body.toUtf8());
    QJsonObject responeJson   = jsonDoc.object();

    qDebug() << "response.status: " << response.status;
    qDebug() << "response.code: " << response.code;

    if(response.status != "success" || response.code != 200)
    {
        handleRequestError(response);
        return;
    }

    if(response.type == ResponseType::CreateUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();
        createBaseUserData(dataJson);
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::ConfirmUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();
        createBaseUserData(dataJson);
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::VerifyUserRequest)
    {
        QJsonObject dataJson = responeJson["data"].toObject();
        createBaseUserData(dataJson);;
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::SearchUserRequest)
    {
        QJsonArray dataArrayJson = responeJson["data"].toArray();

        if(dataArrayJson.size() > 0 )
        {
            QJsonObject dataJson = dataArrayJson[0].toObject();
            createBaseUserData(dataJson);
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
            createBaseUserData(dataJson);
            createPrizesUserData(dataJson);
            createGameUserData(dataJson);

            UserObject userObject;
            userObject.baseUserData = baseUserData();
            userObject.prizesUserData = prizesUserData();
            userObject.gameUserData = gameUserData();

            emit newUserEntered(userObject);
            emit serverRequestSuccess(response.type);
        }
        else
        {
            emit userNotFound();
            qDebug()<<"===== nobody was found =====";
        }
    }
    else if(response.type == ResponseType::ConfirmPrizeRequest)
    {
        qDebug()<<"=====ConfirmPrizeRequest=====";
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::StartGameRequest)
    {
        emit userStartedGame();
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::UpdateGameRequest)
    {
        emit userUpdatedGame();
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::FinishGameRequest)
    {
        emit userFinishedGame();
        emit serverRequestSuccess(response.type);
    }
    else if(response.type == ResponseType::GetDealersRequest)
    {
        qDebug()<<"===== GetDealersRequest =====";
        //QJsonObject dataJson = responeJson["data"].toObject();
    }
}

void ServerRemoteComponent::handleRequestError(const ServerResponse& response)
{
    qDebug() << "server error: " << (int)response.type;

    if(response.type == ResponseType::CreateUserRequest)
    {
        if(response.code == (int)RegErrorType::UserAlreadyExists)
        {
            qDebug() << "User already exists: ";
            emit userAlreadyExists();
        }
    }
    else if(response.type == ResponseType::ConfirmUserRequest)
    {
        if(response.code == (int)RegErrorType::UserAlreadyConfirmed)
        {
            qDebug() << "User already confirmed: ";
            emit userAlreadyConfirmed();
        }
    }

    serverRequestError(response.type);
}


void ServerRemoteComponent::createBaseUserData(const QJsonObject& object)
{
    BaseUserData baseUserData;
    baseUserData.id = object["id"].toInt();
    baseUserData.name = object["name"].toString();
    baseUserData.surname = object["surname"].toString();
    baseUserData.email = object["email"].toString();
    baseUserData.phone = object["phone"].toString();
    baseUserData.confirmed = object["confirmed"].toInt();
    baseUserData.remainSeconds = object["remainSeconds"].toInt();
    baseUserData.test = object["test"].toInt();
    baseUserData.print();
    setBaseUserData(baseUserData);
}

void ServerRemoteComponent::createPrizesUserData(const QJsonObject& object)
{
    PrizesUserData prizesUserData;
    QJsonArray prizesJson = object["prizes"].toArray();

    for(auto prize : prizesJson)
    {
        auto prizeObj = prize.toObject();
        if(prizeObj["type"].toInt() == 1)
        {
            prizesUserData.prize1 = prizeObj["status"].toInt() == 1;
            //qDebug()<<"cola status"<<prizesUserData.prize1 ;
        }
        else if(prizeObj["type"].toInt() == 2)
        {
            prizesUserData.prize2 = prizeObj["status"].toInt() == 1;
            //qDebug()<<"car status"<<prizesUserData.prize2;
        }
    }

    setPrizesUserData(prizesUserData);
}

void ServerRemoteComponent::createGameUserData(const QJsonObject& object)
{
    GameUserData gameUserData;
    QJsonArray gamesJson = object["games"].toArray();

    if(gamesJson.size() > 0)
    {
        QJsonObject gameJson = gamesJson[0].toObject();
        gameUserData.startGame = gameJson["start_game"].toString();
        gameUserData.stage1 = gameJson["stage_1"].toString();
        gameUserData.stage2 = gameJson["stage_2"].toString();
        gameUserData.stage3 = gameJson["stage_3"].toString();
        gameUserData.finishGame = gameJson["finish_game"].toString();
        gameUserData.status = gameJson["status"].toInt();
        setGameUserData(gameUserData);
    }
}

//======================== SET/GET ========================//
//=========================================================//
//=========================================================//

void ServerRemoteComponent::setBaseUserData(const BaseUserData& value)
{
    _baseUserData = value;
    emit baseUserDataRecived(_baseUserData);
}

BaseUserData ServerRemoteComponent::baseUserData() const
{
    return _baseUserData;
}

void ServerRemoteComponent::setPrizesUserData(const PrizesUserData& prizesUserData)
{
    _prizesUserData = prizesUserData;
}

PrizesUserData ServerRemoteComponent::prizesUserData() const
{
    return _prizesUserData;
}

void ServerRemoteComponent::setGameUserData(const GameUserData& gameUserData)
{
    _gameUserData = gameUserData;
}

GameUserData ServerRemoteComponent::gameUserData() const
{
    return _gameUserData;
}
