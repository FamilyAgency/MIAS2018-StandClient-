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




  //  setPrizes();
  //  setGames();

    setUserState(UserData::UserState::CanPlay);
    setLoginState(UserData::LoginState::Login);

//    if(!exist())
//    {
//        setUserState(UserData::UserState::DoesntExists);
//        return;
//    }

//    if(!waitEnoughToPlay())
//    {
//        setUserState(UserData::UserState::WasRecently);
//        return;
//    }

//    if(playingOnAnother())
//    {
//        setUserState(UserData::UserState::YouArePlaying);
//        return;
//    }

//    if(finished())
//    {
//        setUserState(UserData::UserState::Finished);
//        return;
//    }

//    setUserState(UserData::UserState::CanPlay);
//    setLoginState(UserData::LoginState::Login);
}

void UserData::setBaseUserData(const BaseUserInfo& value)
{
    _baseUserData = value;
    emit baseUserDataChanged();
}

BaseUserInfo UserData::baseUserData() const
{
    return _baseUserData;
}

void UserData::setPrizesUserData(const PrizesUserData& value)
{
    _prizesUserData = value;
    emit prizesUserDataChanged();
}

PrizesUserData UserData::prizesUserData() const
{
    return _prizesUserData;
}

void UserData::setGameUserData(const GameUserData& value)
{
    _gameUserData = value;
    emit gameUserDataChanged();
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

OneGameData UserData::getCurrentStage() const
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

