#include "ServerComponentTest.h"
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QTimer.h>

ServerComponentTest::ServerComponentTest(QObject *parent) : ServerComponent(parent)
{
    name = "Server Test";
}

void ServerComponentTest::fetchUserWithGameId(int rfid, int gameId)
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    lastRfid = rfid;
    lastGameId = gameId;
    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onFetchUser()));
}

void ServerComponentTest::onFetchUser()
{
    response.clear();
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("id", QJsonValue::fromVariant(lastRfid));
    userObject.insert("name", QJsonValue::fromVariant("Ivan"));
    userObject.insert("surname", QJsonValue::fromVariant("Ivanov"));
    userObject.insert("firstTime", QJsonValue::fromVariant(true));
    userObject.insert("waitEnoughToPlay", QJsonValue::fromVariant(true));
    userObject.insert("finished", QJsonValue::fromVariant(false));
    userObject.insert("gameMaxTime", QJsonValue::fromVariant(3000));
    userObject.insert("currentGameId", QJsonValue::fromVariant(lastGameId));

    QJsonArray prizesArray;
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    prizesArray.insert(0, QJsonValue::fromVariant(false));
    userObject.insert("prizes", QJsonValue::fromVariant(prizesArray));

    QJsonArray gamesArray;
    QJsonObject gameObject1;
    gameObject1.insert("id", QJsonValue::fromVariant(1));
    gameObject1.insert("complete", QJsonValue::fromVariant(lastGameId > 1));
    gameObject1.insert("time", QJsonValue::fromVariant(12000));
    gameObject1.insert("description", QJsonValue::fromVariant("some game 1"));

    QJsonArray jsonArray = createPathJsonArray(createPath(1));
    gameObject1.insert("path", QJsonValue::fromVariant(jsonArray));
    gameObject1.insert("difficult", QJsonValue::fromVariant(createDiffJsonObject(createDifficult(1))));

    QJsonObject gameObject2;
    gameObject2.insert("id", QJsonValue::fromVariant(2));
    gameObject2.insert("complete", QJsonValue::fromVariant(lastGameId > 2));
    gameObject2.insert("time", QJsonValue::fromVariant(12000));
    gameObject2.insert("description", QJsonValue::fromVariant("some game 2"));


    jsonArray = createPathJsonArray(createPath(2));
    gameObject2.insert("path", QJsonValue::fromVariant(jsonArray));
    gameObject2.insert("difficult", QJsonValue::fromVariant(createDiffJsonObject(createDifficult(2))));


    QJsonObject gameObject3;
    gameObject3.insert("id", QJsonValue::fromVariant(3));
    gameObject3.insert("complete", QJsonValue::fromVariant(lastGameId > 3));
    gameObject3.insert("time", QJsonValue::fromVariant(12000));
    gameObject3.insert("description", QJsonValue::fromVariant("some game 3"));

    jsonArray = createPathJsonArray(createPath(3));
    gameObject3.insert("path", QJsonValue::fromVariant(jsonArray));
    gameObject3.insert("difficult", QJsonValue::fromVariant(createDiffJsonObject(createDifficult(3))));

    gamesArray.insert(0, QJsonValue::fromVariant(gameObject1));
    gamesArray.insert(1, QJsonValue::fromVariant(gameObject2));
    gamesArray.insert(2, QJsonValue::fromVariant(gameObject3));

    userObject.insert("games", QJsonValue::fromVariant(gamesArray));
    QJsonDocument doc(userObject);
    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::fetchDoesntExistUser(int rfid)
{
    if(!canRunRequest())
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
    response.clear();
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
    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::fetchPlayedRecentUser(int rfid)
{
    if(!canRunRequest())
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
    response.clear();
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("id", QJsonValue::fromVariant(lastRfid));
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
    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::fetchAlreadyPlayingUser(int rfid)
{
    if(!canRunRequest())
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
    response.clear();
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("id", QJsonValue::fromVariant(lastRfid));
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
    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::finishedWithPrizes(int rfid)
{
    if(!canRunRequest())
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
    response.clear();
    response.type = ResponseType::UserFetched;

    QJsonObject userObject;
    userObject.insert("exist", QJsonValue::fromVariant(true));
    userObject.insert("id", QJsonValue::fromVariant(lastRfid));
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
    httpRequestSuccessHandler(doc.toJson());
}

void ServerComponentTest::simulateServerTimeout()
{
    if(!canRunRequest())
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
    if(!canRunRequest())
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

void ServerComponentTest::logout()
{
    if(!canRunRequest())
    {
        qDebug()<<"wait for server please";
        return;
    }

    setServerStatus(ServerStatus::Busy);

    QTimer::singleShot(1000, this, SLOT(onUserLogout()));
}

void ServerComponentTest::onUserLogout()
{
    response.clear();
    response.type = ResponseType::Logout;
    httpRequestSuccessHandler("Logout");
}



QVector<QPointF> ServerComponentTest::createPath(int pathId)
{
    QVector<QPointF> path;
    QPointF point1 = QPointF(388, 88);
    QPointF point2 = QPointF(621, 71 );
    QPointF point3 = QPointF(970, 114);
    QPointF point4 = QPointF(223, 222);
    QPointF point5 = QPointF(347, 243);
    QPointF point6 = QPointF(467, 264);
    QPointF point7 = QPointF(690, 300);
    QPointF point8 = QPointF(987, 207);
    QPointF point9 = QPointF(218, 422);
    QPointF point10 = QPointF(511, 357);
    QPointF point11 = QPointF(969, 389);
    QPointF point12 = QPointF(1152, 379);
    QPointF point13 = QPointF(315, 537);
    QPointF point14 = QPointF(573, 417);
    QPointF point15 = QPointF(666, 500);
    QPointF point16 = QPointF(735, 458);
    QPointF point17 = QPointF(917, 495);
    QPointF point18 = QPointF(913, 570);
    QPointF point19 = QPointF(1144, 616);
    QPointF point20 = QPointF(1002, 316);

    //penta
    //path.clear();
    //path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
    //velocitycalculator.setLimits(0, 3.5, 40);
    //gameTasks.append(new GameTask(path, velocitycalculator));

    path.clear();

    switch(pathId)
    {
    case 1:
        path<<point4<<point6<<point10<<point7<<point16<<point17;
        break;

    case 2:
        path<<point17<<point20<<point3<<point2;
        break;

    case 3:
        path<<point2<<point1<<point6<<point5<<point9;
        break;

    case 4:
        path<<point9<<point13<<point10<<point14<<point15<<point16<<point17<<point18<<point19;
        break;

    case 5:
        path<<point19<<point12<<point11<<point20<<point8<<point10<<point1;
        break;
    }

    return path;
}

VelocityCalculator ServerComponentTest::createDifficult(int diff)
{
    VelocityCalculator velocitycalculator;
    switch(diff)
    {
    case 0:
        velocitycalculator.setLimits(2.0f, 2.5f, 30.0f);
        break;

    case 1:
        velocitycalculator.setLimits(2.0f, 3.5f, 40.0f);
        break;

    case 2:
        velocitycalculator.setLimits(2.0f, 3.3f, 45.0f);
        break;

    case 3:
        velocitycalculator.setLimits(2, 3, 60);
        break;

    case 4:
        velocitycalculator.setLimits(2, 2, 70);
        break;

    case 5:
        velocitycalculator.setLimits(2, 3, 75);
        break;
    }

    return velocitycalculator;
}

QJsonArray ServerComponentTest::createPathJsonArray(const QVector<QPointF>& path)
{
    QJsonArray jsonArray;

    for (auto &point : path)
    {
        QJsonObject jsonPoint;
        jsonPoint.insert("x", point.x());
        jsonPoint.insert("y", point.y());
        jsonArray.append(jsonPoint);
    }
    return jsonArray;
}

QJsonObject ServerComponentTest::createDiffJsonObject(const VelocityCalculator& velCalc)
{
    QJsonObject diffObject;
    diffObject.insert("humanValueThresholdMax", velCalc.humanValueThresholdMax);
    diffObject.insert("humanValueThresholdMin", velCalc.humanValueThresholdMin);
    diffObject.insert("minVelocity", velCalc.minVelocity);
    diffObject.insert("maxVelocity", velCalc.maxVelocity);
    diffObject.insert("minBackVelocity", velCalc.minBackVelocity);
    diffObject.insert("maxBackVelocity", velCalc.maxBackVelocity);
    return diffObject;
}
