#include "UserData.h"
#include <QQmlEngine>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug>


UserData::UserData(QObject *parent) : QObject(parent)
{
    QVariantList prizes;
    prizes.append(false);
    prizes.append(false);
    setPrizes(prizes);
}

UserData::~UserData()
{

}

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
}

void UserData::setUserState(UserState value)
{
    userState = value;
    emit userStateChanged(value);
}

void UserData::setLoginState(LoginState value)
{
    loginState = value;
    emit loginStateChanged(value);
}

QString UserData::getStringState() const
{
    switch(loginState)
    {
    case LoginState::Login: return "User login";
    case LoginState::Logout: return "User logout";
    }
    return "undefined";
}

QVariantList UserData::prizes() const
{
    return _prizes;
}

void UserData::setPrizes(const QVariantList& value)
{
    _prizes = value;
    emit prizesChanged();
}

QString UserData::name() const
{
    return _name;
}

QString UserData::surname() const
{
    return _surname;
}

int UserData::id() const
{
    return _id;
}

bool UserData::exist() const
{
    return _exist;
}

bool UserData::firstTime() const
{
    return _firstTime;
}

bool UserData::finished() const
{
    return _finished;
}

bool UserData::waitEnoughToPlay() const
{
    return _waitEnoughToPlay;
}

bool UserData::playingOnAnother() const
{
    return _playingOnAnother;
}

void UserData::setName(const QString& value)
{
    _name = value;
    emit nameChanged();
}

void UserData::setSurname(const QString& value)
{
    _surname = value;
    emit surnameChanged();
}

void UserData::setId(int value)
{
    _id = value;
    emit idChanged();
}

void UserData::setExist(bool value)
{
    _exist = value;
    emit existChanged();
}

void UserData::setFirstTime(bool value)
{
    _firstTime = value;
    emit firstTimeChanged();
}

void UserData::setFinished(bool value)
{
    _finished = value;
    emit finishedChanged();
}

void UserData::setWaitEnoughToPlay(bool value)
{
    _waitEnoughToPlay = value;
    emit waitEnoughToPlayChanged();
}

void UserData::setPlayingOnAnother(bool value)
{
    _playingOnAnother = value;
    emit playingOnAnotherChanged();
}

void UserData::setGameProgess(const GameProgress& value)
{
    gameProgress = value;
}

GameProgress UserData::getGameProgess() const
{
    return gameProgress;
}

OneGameData UserData::getCurrentGameData() const
{
    return gameProgress.getCurrentGameData();
}

void UserData::currentGameCompleted(int time)
{
    gameProgress.currentGameCompleted(time);
    updateGameProgressData();
}

bool UserData::hasGames() const
{
    return gameProgress.hasGames();
}

void UserData::setConfig(ConfigPtr value)
{
   setGameConfig(*value->standGamesConfig);
}

void UserData::setGameConfig(StandGamesConfig config)
{
    _gameConfig = config;
    emit gameConfigChanged();
}

void UserData::setGameCategory(int id)
{
    qDebug()<<"setGameCategory  "<< id;
    auto choosenGame = _gameConfig.games[id];
    auto description = choosenGame.description;
    emit descriptionChanged(description);

    QVector<OneGameData> games;
    OneGameData oneGameData1;
    oneGameData1.setId(1);
    oneGameData1.setComplete(false);
    oneGameData1.setTime(0.0f);
    oneGameData1.setDescription("");
    oneGameData1.setPath(choosenGame.path1);
    oneGameData1.setDifficult(VelocityCalculator(2, 3, 60));
    games.push_back(oneGameData1);

    OneGameData oneGameData2;
    oneGameData2.setId(2);
    oneGameData2.setComplete(false);
    oneGameData2.setTime(0.0f);
    oneGameData2.setDescription("");
    oneGameData2.setPath(choosenGame.path2);
    oneGameData2.setDifficult(VelocityCalculator(2, 2, 70));
    games.push_back(oneGameData2);

    OneGameData oneGameData3;
    oneGameData3.setId(3);
    oneGameData3.setComplete(false);
    oneGameData3.setTime(0.0f);
    oneGameData3.setDescription("");
    oneGameData3.setPath(choosenGame.path3);
    oneGameData3.setDifficult(VelocityCalculator(2, 2, 70));
    games.push_back(oneGameData3);

    GameProgress gameProgress;
    gameProgress.setGames(games);
    gameProgress.setCurrentGameId(1);
    setGameProgess(gameProgress);

    updateGameProgressData();   
}

void UserData::clearData()
{
    gameProgress.setCleanTime(0.0f);
    gameProgress.setCurrentGameId(0);
    gameProgress.setGamesCount(0);
    gameProgress.setGamesCompleteCount(0);
}

void UserData::parse(const QString& userObject)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(userObject.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();

    setName(jsonObj["name"].toString());
    setSurname(jsonObj["surname"].toString());
    setId(jsonObj["id"].toInt());
    setFirstTime(true);
    setFinished(false);
    setExist(jsonObj["exist"].toBool());
    setWaitEnoughToPlay(jsonObj["waitEnoughToPlay"].toBool());
    setPlayingOnAnother(jsonObj["playingOnAnother"].toBool());
    setFinished(jsonObj["finished"].toBool());

    auto prizesJson = jsonObj["prizes"].toArray();
    QVariantList prizes;
    prizes.append(prizesJson[0].toBool());
    prizes.append(prizesJson[1].toBool());
    setPrizes(prizes);

//    auto gamesJson = jsonObj["games"].toArray();
//    QVector<OneGameData> games;
//    for(int i = 0; i < gamesJson.size(); i++)
//    {
//        auto gameJson = gamesJson[i].toObject();
//        OneGameData oneGameData;
//        oneGameData.setId(gameJson["id"].toInt());
//        oneGameData.setComplete(gameJson["complete"].toBool());
//        oneGameData.setTime(gameJson["time"].toInt());
//        oneGameData.setDescription(gameJson["description"].toString());

//        auto diffObject = gameJson["difficult"].toObject();
//        auto humanValueThresholdMax = diffObject["humanValueThresholdMax"].toDouble();
//        auto humanValueThresholdMin = diffObject["humanValueThresholdMin"].toDouble();
//        auto minVelocity = diffObject["minVelocity"].toDouble();
//        auto maxVelocity = diffObject["maxVelocity"].toDouble();
//        auto minBackVelocity = diffObject["minBackVelocity"].toDouble();
//        auto maxBackVelocity = diffObject["maxBackVelocity"].toDouble();

//        oneGameData.setDifficult
//                (VelocityCalculator
//                 (minVelocity,
//                  maxVelocity,
//                  humanValueThresholdMin,
//                  humanValueThresholdMax,
//                  minBackVelocity,
//                  maxBackVelocity));

//        QVector<QPointF> path;
//        auto pathArray = gameJson["path"].toArray();
//        for(auto pointJson: pathArray)
//        {
//            QPointF point;
//            point.setX(pointJson.toObject()["x"].toDouble());
//            point.setY(pointJson.toObject()["y"].toDouble());
//            path.push_back(point);
//        }
//        oneGameData.setPath(path);
//        games.push_back(oneGameData);
//    }



    if(!exist())
    {
        setUserState(UserData::UserState::DoesntExists);
        return;
    }

    if(!waitEnoughToPlay())
    {
        setUserState(UserData::UserState::WasRecently);
        return;
    }

    if(playingOnAnother())
    {
        setUserState(UserData::UserState::YouArePlaying);
        return;
    }

    if(finished())
    {
        setUserState(UserData::UserState::Finished);
        return;
    }

    setUserState(UserData::UserState::CanPlay);
    setLoginState(UserData::LoginState::Login);
}

void UserData::setUserDoesntExist()
{
     setUserState(UserData::UserState::DoesntExists);
}

void UserData::setNewUserData(const UserObject& userObject)
{
    auto baseuserInfo =  userObject.baseUserInfo;

    setName(baseuserInfo.name);
    setSurname(baseuserInfo.surname);
    setId(baseuserInfo.id);

    setUserState(UserData::UserState::CanPlay);
    setLoginState(UserData::LoginState::Login);
}

void UserData::updateGameProgressData()
{
    qDebug()<<":::::::::::::::::: updateGameProgressData ::::::::::::::::::  ";

    setCleanGameTime(gameProgress.cleanTime());
    setCurrentGameId(gameProgress.currentGameId());
    setGamesCompleteCount(gameProgress.gamesCompleteCount());
    setGamesCount(gameProgress.gamesCount());

    qDebug()<<":::::::::::::::::: gameProgress.gamesCompleteCount() ::::::::::::::::::  "<<gameProgress.gamesCompleteCount();

}

void UserData::setCleanGameTime(float value)
{
    _cleanGameTime = value;
    emit cleanGameTimeChanged();
}

float UserData::cleanGameTime() const
{
    return _cleanGameTime;
}

void UserData::setCurrentGameId(int stage)
{
    _currentGameId = stage;
     emit currentGameIdChanged();
}

int UserData::currentGameId() const
{
    return _currentGameId;
}

void UserData::setGamesCount(int count)
{
    _gamesCount = count;
    emit gamesCountChanged();
}

int UserData::gamesCount() const
{
    return _gamesCount;
}

void UserData::setGamesCompleteCount(int count)
{
    _gamesCompleteCount = count;
    emit gamesCompleteCountChanged();
}

int UserData::gamesCompleteCount() const
{
    return _gamesCompleteCount;
}

