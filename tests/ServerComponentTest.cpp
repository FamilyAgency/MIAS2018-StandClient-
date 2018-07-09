#include "ServerComponentTest.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QTimer.h>

ServerComponentTest::ServerComponentTest(QObject *parent) : ServerComponent(parent)
{
    name = "Server Test";
}

void ServerComponentTest::fetchUser(int rfid)
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(4000, this, SLOT(onFetchUser()));
}

void ServerComponentTest::onFetchUser()
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("userId", QJsonValue::fromVariant(lastRfid));
    userObject.insert("name", QJsonValue::fromVariant("Ivan"));
    userObject.insert("surname", QJsonValue::fromVariant("Ivanov"));
    userObject.insert("firstTime", QJsonValue::fromVariant(true));
    userObject.insert("waitEnoughToPlay", QJsonValue::fromVariant(true));
    userObject.insert("finished", QJsonValue::fromVariant(false));
    userObject.insert("gameMaxTime", QJsonValue::fromVariant(3000));
    userObject.insert("currentGameId", QJsonValue::fromVariant(1));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("gameId", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(false));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject2;
    gameObject2.insert("gameId", QJsonValue::fromVariant(1));
    gameObject2.insert("complete", QJsonValue::fromVariant(false));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject3;
    gameObject3.insert("gameId", QJsonValue::fromVariant(1));
    gameObject3.insert("complete", QJsonValue::fromVariant(false));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));

    QJsonDocument doc(userObject);

    switch(lastRfid)
    {
    case 1000:

        break;

    case 1001:

        break;
    }

    httpRequestSuccessHandler(doc.toJson());
}




void ServerComponentTest::fetchDoesntExistUser(int rfid)
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onFetchDoesntExistUser()));
}

void ServerComponentTest::onFetchDoesntExistUser()
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(false));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("gameId", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(false));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject2;
    gameObject2.insert("gameId", QJsonValue::fromVariant(1));
    gameObject2.insert("complete", QJsonValue::fromVariant(false));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject3;
    gameObject3.insert("gameId", QJsonValue::fromVariant(1));
    gameObject3.insert("complete", QJsonValue::fromVariant(false));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));

    QJsonDocument doc(userObject);

    switch(lastRfid)
    {
    case 1000:

        break;

    case 1001:

        break;
    }

    httpRequestSuccessHandler(doc.toJson());
}


void ServerComponentTest::fetchPlayedRecentUser(int rfid)
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onFetchPlayedRecentUser()));
}

void ServerComponentTest::onFetchPlayedRecentUser()
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("userId", QJsonValue::fromVariant(lastRfid));
    userObject.insert("name", QJsonValue::fromVariant("Igor"));
    userObject.insert("surname", QJsonValue::fromVariant("Igor"));
    userObject.insert("firstTime", QJsonValue::fromVariant(true));
    userObject.insert("waitEnoughToPlay", QJsonValue::fromVariant(false));
    userObject.insert("finished", QJsonValue::fromVariant(false));
    userObject.insert("gameMaxTime", QJsonValue::fromVariant(3000));
    userObject.insert("currentGameId", QJsonValue::fromVariant(1));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("gameId", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(false));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject2;
    gameObject2.insert("gameId", QJsonValue::fromVariant(1));
    gameObject2.insert("complete", QJsonValue::fromVariant(false));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject3;
    gameObject3.insert("gameId", QJsonValue::fromVariant(1));
    gameObject3.insert("complete", QJsonValue::fromVariant(false));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));

    QJsonDocument doc(userObject);

    switch(lastRfid)
    {
    case 1000:

        break;

    case 1001:

        break;
    }

    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::fetchAlreadyPlayingUser(int rfid)
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onFetchAlreadyPlayingUser()));
}

void ServerComponentTest::onFetchAlreadyPlayingUser()
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("userId", QJsonValue::fromVariant(lastRfid));
    userObject.insert("name", QJsonValue::fromVariant("Igor"));
    userObject.insert("surname", QJsonValue::fromVariant("Igor"));
    userObject.insert("firstTime", QJsonValue::fromVariant(true));
    userObject.insert("waitEnoughToPlay", QJsonValue::fromVariant(true));
    userObject.insert("playingOnAnother", QJsonValue::fromVariant(true));
    userObject.insert("finished", QJsonValue::fromVariant(false));
    userObject.insert("gameMaxTime", QJsonValue::fromVariant(3000));
    userObject.insert("currentGameId", QJsonValue::fromVariant(1));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("gameId", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(false));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject2;
    gameObject2.insert("gameId", QJsonValue::fromVariant(1));
    gameObject2.insert("complete", QJsonValue::fromVariant(false));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject3;
    gameObject3.insert("gameId", QJsonValue::fromVariant(1));
    gameObject3.insert("complete", QJsonValue::fromVariant(false));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));

    QJsonDocument doc(userObject);

    switch(lastRfid)
    {
    case 1000:

        break;

    case 1001:

        break;
    }

    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::finishedWithPrizes(int rfid)
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onFinishedWithPrizes()));
}

void ServerComponentTest::onFinishedWithPrizes()
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("userId", QJsonValue::fromVariant(lastRfid));
    userObject.insert("name", QJsonValue::fromVariant("Igor"));
    userObject.insert("surname", QJsonValue::fromVariant("Igor"));
    userObject.insert("firstTime", QJsonValue::fromVariant(true));
    userObject.insert("waitEnoughToPlay", QJsonValue::fromVariant(true));
    userObject.insert("playingOnAnother", QJsonValue::fromVariant(false));
    userObject.insert("finished", QJsonValue::fromVariant(true));
    userObject.insert("gameMaxTime", QJsonValue::fromVariant(3000));
    userObject.insert("currentGameId", QJsonValue::fromVariant(1));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("gameId", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(false));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject2;
    gameObject2.insert("gameId", QJsonValue::fromVariant(1));
    gameObject2.insert("complete", QJsonValue::fromVariant(false));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));

    QJsonObject gameObject3;
    gameObject3.insert("gameId", QJsonValue::fromVariant(1));
    gameObject3.insert("complete", QJsonValue::fromVariant(false));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));

    QJsonDocument doc(userObject);

    switch(lastRfid)
    {
    case 1000:

        break;

    case 1001:

        break;
    }

    httpRequestSuccessHandler(doc.toJson());
}


void ServerComponentTest::simulateServerTimeout()
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    setServerStatus(ServerStatus::Busy);
    QTimer::singleShot(1000, this, SLOT(onSimulateServerTimeout()));
}

void ServerComponentTest::onSimulateServerTimeout()
{
    httpRequestFailedHandler("Error: Simulate Server Timeout");
}

void ServerComponentTest::simulateServerError()
{
    if(_serverStatus == ServerStatus::Busy)
    {
        qDebug()<<"wait for server please";
        return;
    }

    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onSimulateServerError()));
}

void ServerComponentTest::onSimulateServerError()
{
   httpRequestFailedHandler("Error: Simulate Server Error");
}





