#include "GameProgress.h"

GameProgress::GameProgress(QObject *parent) : QObject(parent)
{

}

void GameProgress::setQmlContext(QQmlContext* qmlContext)
{
    //qmlContext = value;
    qmlContext->setContextProperty("gameProgress", this);
}

void GameProgress::setCurrentStage(int stage)
{
    _currentStage = stage;
    emit currentStageChanged();
}

int GameProgress::currentStage() const
{
    return _currentStage;
}

void GameProgress::setGamesCount(int count)
{
    _gamesCount = count;
    emit gamesCountChanged();
}

int GameProgress::gamesCount() const
{
    return _gamesCount;
}

void GameProgress::setGamesCompleteCount(int count)
{
    _gamesCompleteCount = count;
    emit gamesCompleteCountChanged();
}

int GameProgress::gamesCompleteCount() const
{
    return _gamesCompleteCount;
}

void GameProgress::setGames(const QVector<OneGameData>& data)
{
    gamesData = data;
    setGamesCount(gamesData.length());
}

void GameProgress::setStageCompletionTime(float time)
{
    complitionTime = time;
}

QVector<OneGameData> GameProgress::getGames() const
{
    return gamesData;
}

void GameProgress::setCleanTime(float value)
{
    _cleanTime = value;
    emit cleanTimeChanged();
}

float GameProgress::cleanTime() const
{
    return _cleanTime;
}

