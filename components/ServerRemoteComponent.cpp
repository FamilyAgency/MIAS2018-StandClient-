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
                                              const QString& phone)
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
    query.addQueryItem("test", _serverConfig.serverAPI.testUser);

    qDebug()<<"fullRequest "<<serverConfig().url + "/users/register";
    qDebug()<<"_serverConfig.serverAPI.testUser "<<_serverConfig.serverAPI.testUser;
    httpClient->runPostRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
}

void ServerRemoteComponent::createUserRequest()
{
    createUserRequest("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                      "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                      "яндекс@почта.рф",
                      "+79067704595");

    //    createUserRequest("Вика",
    //                      "Журавлева",
    //                      "vika@gmail.com",
    //                      "+89151546522");
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
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::ConfirmPrizeRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/prizes/" + QString::number(prizeid);
    QNetworkRequest request(fullRequest);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery query;
    // query.addQueryItem("status", QString::number(1));
    // query.addQueryItem("type", QString::number(1));
    httpClient->runPutRequest(request, query.toString(QUrl::FullyEncoded).toUtf8());
}


void ServerRemoteComponent::startGameRequest(int userId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::StartGameRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/games/start";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::updateGameRequest(int userId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::UpdateGameRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/games/update";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::finishGameRequest(int userId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::FinishGameRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = serverConfig().url + "/users/" + QString::number(userId) + "/games/finish";
    httpClient->runGetRequest(fullRequest);
}

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
            createPrizesUserData(dataJson);
            createGameUserData(dataJson);

            UserObject userObject;
            userObject.baseUserInfo = baseUserInfo();
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
}

void ServerRemoteComponent::handleRequestError(const ServerResponse& response)
{
    qDebug() << "server error: " << (int)response.type;

    if(response.type == ResponseType::CreateUserRequest)
    {
        if(response.code == 555)
        {
            qDebug() << "User already exists: ";
            emit userAlreadyExists();
            return;
        }
    }

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

void ServerRemoteComponent::setPrizesUserData(const PrizesUserData& prizesUserData)
{
    _prizesUserData = prizesUserData;
    emit prizesUserDataChanged();
}

PrizesUserData ServerRemoteComponent::prizesUserData() const
{
    return _prizesUserData;
}

void ServerRemoteComponent::setGameUserData(const GameUserData& gameUserData)
{
    _gameUserData = gameUserData;
    emit gameUserDataChanged();
}

GameUserData ServerRemoteComponent::gameUserData() const
{
    return _gameUserData;
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
    QJsonObject gameJson = gamesJson[0].toObject();


    gameUserData.startGame = gameJson["start_game"].toString();
    gameUserData.stage1 = gameJson["stage_1"].toString();
    gameUserData.stage2 = gameJson["stage_2"].toString();
    gameUserData.stage3 = gameJson["stage_3"].toString();
    gameUserData.finishGame = gameJson["finish_game"].toString();

    setGameUserData(gameUserData);
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

    QString fullRequest = "http://mias2018.familyagency.ru";
    httpClient->runGetRequest(fullRequest);
}

void ServerRemoteComponent::simulateServerTimeout()
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    response.clear();
    response.type = ResponseType::VerifyUserRequest;
    setServerStatus(ServerStatus::Busy);

    QString fullRequest = "http://familyagency.ru/lab/infloop.php";
    httpClient->runGetRequest(fullRequest);
}
