#include "ServerComponentTest.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QTimer.h>

ServerComponentTest::ServerComponentTest(QObject *parent) : ServerComponent(parent)
{
    name = "Server Test";
}

void ServerComponentTest::fetchUser(int deviceId, int rfid)
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("userId", QJsonValue::fromVariant(rfid));
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

    switch(rfid)
    {
        case 1000:
             response.body = doc.toJson();
        break;

        case 1001:
             response.body = doc.toJson();
        break;
    }

   // QTimer::singleShot(1000, this, [&]() { emit serverResponse(response);});
emit serverResponse(response);
}

