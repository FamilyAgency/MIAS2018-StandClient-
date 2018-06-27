#include "GameProgress.h"

GameProgress::GameProgress(QObject *parent) : QObject(parent)
{

}

void GameProgress::setCurrentStage(int stage)
{
    currentStage = stage;
}

void GameProgress::setGames(const QVector<OneGameData>& data)
{
    gamesData = data;
}

void GameProgress::setStageCompletionTime(float time)
{
    complitionTime = time;
}

QVector<OneGameData> GameProgress::getGames() const
{
    return gamesData;
}

