#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QVector>
#include <QQmlContext>
#include "OneGameData.h"

class GameProgress
{

public:
    explicit GameProgress();

    void setCurrentGameId(int stage);
    int currentGameId() const;

    void setGamesCount(int count);
    int gamesCount() const;

    void setGamesCompleteCount(int count);
    int gamesCompleteCount() const;

    void setCleanTime(float count);
    float cleanTime() const;

    void setGames(const QVector<OneGameData>& data);
    void setStageCompletionTime(float time);

    QVector<OneGameData> getGames() const;

    OneGameData getCurrentGameData() const;
    void currentGameCompleted(int time);

    bool hasGames() const;

private:
    QVector<OneGameData> uncompleteGames, completeGames;
    int _currentGameId = 0;
    int _gamesCount = 0;
    int _gamesCompleteCount = 0;
    float complitionTime;
    float _cleanTime = 0.0f;
};

#endif // GAMEPROGRESS_H
