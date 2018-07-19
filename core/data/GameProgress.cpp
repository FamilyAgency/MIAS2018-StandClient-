#include "GameProgress.h"
#include <QDebug>

GameProgress::GameProgress()
{

}

void GameProgress::setCurrentGameId(int stage)
{
    _currentGameId = stage;
}

int GameProgress::currentGameId() const
{
    return _currentGameId;
}

void GameProgress::setGamesCount(int count)
{
    _gamesCount = count;
}

int GameProgress::gamesCount() const
{
    return _gamesCount;
}

void GameProgress::setGamesCompleteCount(int count)
{
    _gamesCompleteCount = count;
}

int GameProgress::gamesCompleteCount() const
{
    return _gamesCompleteCount;
}

void GameProgress::setGames(const QVector<OneGameData>& data)
{
    uncompleteGames.clear();
    completeGames.clear();

    float cleanTime = 0.0f;
   
    for(OneGameData game : data)
    {
        if(!game.complete())
        {
           uncompleteGames.push_back(game);
        }
        else
        {
            completeGames.push_back(game);
            cleanTime += game.getTime();
        }
    }

    setCleanTime(cleanTime);
    setGamesCompleteCount(completeGames.length());
    setGamesCount(data.length());
}

void GameProgress::setStageCompletionTime(float time)
{
    complitionTime = time;
}

QVector<OneGameData> GameProgress::getGames() const
{
    return uncompleteGames;
}

OneGameData GameProgress::getCurrentGameData() const
{
    qDebug()<<":::::::::::::::::: getCurrentGameData :::::::::::::::::: _currentStage "<<_currentGameId;
    qDebug()<<":::::::::::::::::: uncompleteGames :::::::::::::::::: length "<<uncompleteGames.length();

    OneGameData curGameData;
    for(OneGameData game: uncompleteGames)
    {
        if(game.getId() == _currentGameId)
        {
            curGameData = game;
            break;
        }
    }

    return curGameData;
}

void GameProgress::setCleanTime(float value)
{
    _cleanTime = value;
}

float GameProgress::cleanTime() const
{
    return _cleanTime;
}

void GameProgress::currentGameCompleted(int time)
{
    int completeGameIndex = 0;

    for(int i = 0; i < uncompleteGames.length(); i++)
    {
        if(uncompleteGames[i].getId() == _currentGameId)
        {
            uncompleteGames[i].setComplete(true);
            uncompleteGames[i].setTime(time);
            completeGameIndex = i;
            break;
        }
    }

    completeGames.push_back(uncompleteGames[completeGameIndex]);
    uncompleteGames.removeAt(completeGameIndex);
    setGamesCompleteCount(completeGames.length());

    float cleanTime = 0.0f;

    for(int i = 0; i < completeGames.length(); i++)
    {
       cleanTime += completeGames[i].getTime();// * toSeconds;
    }

    setCleanTime(cleanTime);

    if(!uncompleteGames.empty())
    {
      setCurrentGameId(_currentGameId + 1);
    }
}

bool GameProgress::hasGames() const
{
     qDebug()<<" hasGames " << uncompleteGames.length();
    return uncompleteGames.length() > 0;
}

