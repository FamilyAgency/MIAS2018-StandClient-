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
    setBaseUserData(userObject.baseUserData);
    setPrizesUserData(userObject.prizesUserData);
    setGameUserData(userObject.gameUserData);

    checkCanUserPlay();
}

void UserData::setBaseUserData(const BaseUserData& value)
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

    if(finished())
    {
        _canPlay = false;
        if(allPrizesGot())
        {
            cantPlayReason = CantPlayReason::FinishedPrizesGot;
        }
        else
        {
            cantPlayReason = CantPlayReason::FinishedPrizesNotGot;
        }
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
}

int UserData::getSecondsToStart() const
{
    return _baseUserData.remainSeconds;
}

bool UserData::finished() const
{
    return _gameUserData.status == 5;
}

bool UserData::allPrizesGot() const
{    
    return _prizesUserData.prize1 == true;
}

bool UserData::wasRecently() const
{
    return _gameUserData.status != 0;
}

bool UserData::playingOnAnotherStand() const
{
    return _gameUserData.status != 0;
}

CantPlayReason UserData::getReasonCantPlay() const
{
    return cantPlayReason;
}

void UserData::clearBaseUserData()
{
    _baseUserData.clear();
    emit baseUserDataChanged();
}

int UserData::getCurrentStageId() const
{
    return _gameUserData.getCurrentStageId();
}

bool UserData::canPlay() const
{
    return _canPlay;
}

BaseUserData UserData::baseUserData() const
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
    _gameUserData.setCurrentStageId(1);
    emit gameUserDataChanged();
}

QVariantList UserData::getFullGamePath() const
{
    return _gameUserData.getFullGamePath();
}

QVariantList UserData::getTargetPoints() const
{
    return _gameUserData.getTargetPoints();
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

void UserData::superGameCompleted(int time)
{
    _gameUserData.superGameCompleted(time);
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

//======================================================//
//======================================================//
//======================================================//

bool BaseUserData::isPinConfirmed() const
{
    return confirmed == 1;
}

int BaseUserData::getPinToConfirm() const
{
    return confirmed;
}

void BaseUserData::print()
{
    qDebug()<<"===== User Info =====";
    qDebug()<<"id = "<<id;
    qDebug()<<"name = "<<name;
    qDebug()<<"surname = "<<surname;
    qDebug()<<"email = "<<email;
    qDebug()<<"phone = "<<phone;
    qDebug()<<"confirmed = "<<confirmed;
    qDebug()<<"test = "<<test;
    qDebug()<<"====================";
}

void BaseUserData::clear()
{
    id = 0;
    name = "";
    surname = "";
    email = "";
    phone = "";
    confirmed = 0;
    test = 0;
}


GameUserData::GameUserData()
{
    stageTimes.push_back(0.0f);
    stageTimes.push_back(0.0f);
    stageTimes.push_back(0.0f);
}

void GameUserData::setupConfigGameData(const StandOneGameConfig& game)
{
    stages.clear();
    stageTimes.clear();

    description = game.description;
    qDebug()<<"description   "<<description;

    fullGamePath.clear();
    targetPoints.clear();
    for(int i = 0; i < game.stages.size(); i++)
    {
        OneStageData oneGameData;
        oneGameData.setId(i + 1);
        oneGameData.setComplete(false);
        oneGameData.setTime(0.0f);
        auto path = game.stages[i].path;
        oneGameData.setPath(path);

        for(int j = 0; j < path.size(); j++)
        {
            fullGamePath.append(path[j]);
        }

        targetPoints.append(path[path.size() - 1]);

        oneGameData.setDifficult(VelocityCalculator(2, 3, 60));
        oneGameData.setAdvantage(game.stages[i].advantage);
        stages.push_back(oneGameData);
        stageTimes.push_back(0.0f);
    }

    _hasGames = true;
}

QVariantList GameUserData::getFullGamePath() const
{
    return fullGamePath;
}

QVariantList GameUserData::getTargetPoints() const
{
    return targetPoints;
}



void GameUserData::setCurrentStageId(int id)
{
    currentStageId = id;
    currentStage = stages[id - 1];
}

OneStageData GameUserData::getCurrentStage() const
{
    return currentStage;
}

int GameUserData::getCurrentStageId() const
{
    return currentStageId;
}

void GameUserData::currentStageCompleted(int time)
{
    const float toSeconds = 1/1000.0f;
    stageTimes[currentStageId - 1] = time * toSeconds;

    currentStage.setTime(time);
    qDebug()<<"Current game id "<<currentStageId<<stages.size();
    if(currentStageId + 1 <= stages.size())
    {
        _hasGames = true;
        setCurrentStageId(currentStageId + 1);
    }
    else
    {
        _hasGames = false;
    }
}

void GameUserData::superGameCompleted(int time)
{
    const float toSeconds = 1/1000.0f;
    superGameTime = time * toSeconds;
}

bool GameUserData::hasStages() const
{
    return _hasGames;
}
