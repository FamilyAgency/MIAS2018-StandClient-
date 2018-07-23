#include "UserData.h"
#include <QQmlEngine>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>
#include <QDebug>

UserData::UserData(QObject *parent) : QObject(parent)
{

}

UserData::~UserData()
{

}

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
}

void UserData::setNewUserData(const UserObject& userObject)
{
    setBaseUserData(userObject.baseUserInfo);
    setPrizesUserData(userObject.prizesUserData);
    setGameUserData(userObject.gameUserData);

    checkCanUserPlay();
}

void UserData::setBaseUserData(const BaseUserInfo& value)
{
    _baseUserData = value;
    emit baseUserDataChanged();
}

void UserData::setPrizesUserData(const PrizesUserData& value)
{
    _prizesUserData = value;
    emit prizesUserDataChanged();
}

void UserData::setGameUserData(const GameUserData& value)
{
    _gameUserData = value;
    emit gameUserDataChanged();
}

void UserData::checkCanUserPlay()
{
    cantPlayReason = CantPlayReason::None;
    _canPlay = true;

    if(allPrizesGot())
    {
        _canPlay = false;
        cantPlayReason = CantPlayReason::Finished;
    }
    else if(wasRecently())
    {
        _canPlay = false;
        cantPlayReason = CantPlayReason::WasRecently;
    }
    else if(playingOnAnotherStand())
    {
        _canPlay = false;
        cantPlayReason = CantPlayReason::YouArePlaying;
    }

    if(!_canPlay)
    {
        emit userCantStartReason(cantPlayReason);
    }
}

bool UserData::allPrizesGot() const
{
    return false;
}

bool UserData::wasRecently() const
{
    return false;
}

bool UserData::playingOnAnotherStand() const
{
    return false;
}

UserData::CantPlayReason UserData::getReasonCantPlay() const
{
    return cantPlayReason;
}

bool UserData::canPlay() const
{
    return _canPlay;
}



BaseUserInfo UserData::baseUserData() const
{
    return _baseUserData;
}

PrizesUserData UserData::prizesUserData() const
{
    return _prizesUserData;
}

GameUserData UserData::gameUserData() const
{
    return _gameUserData;
}

void UserData::setGameCategory(int id)
{
    qDebug()<<"setGameCategory  "<< id;
    StandOneGameConfig choosenGame = _gameConfig.games[id];
    _gameUserData.setupConfigGameData(choosenGame);
    _gameUserData.setCurrentGameId(1);
    emit gameUserDataChanged();
}

OneStageData UserData::getCurrentStage() const
{
    return _gameUserData.getCurrentStage();
}

void UserData::currentStageCompleted(int time)
{
    _gameUserData.currentStageCompleted(time);
    emit gameUserDataChanged();
}

bool UserData::hasStages() const
{
    return _gameUserData.hasStages();
}

void UserData::setConfig(ConfigPtr value)
{
    setGameConfig(*value->standGamesConfig);
    superGameConfig = _gameConfig.superGame;
}

SuperGameConfig UserData::getSuperGameData() const
{
    return superGameConfig;
}

void UserData::setGameConfig(StandGamesConfig config)
{
    _gameConfig = config;
}

void UserData::clearData()
{

}

