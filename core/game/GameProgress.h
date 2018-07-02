#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QVector>
#include <QQmlContext>
#include "OneGameData.h"

class GameProgress : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentGameId READ currentGameId WRITE setCurrentGameId NOTIFY currentGameIdChanged)
    Q_PROPERTY(int gamesCount READ gamesCount WRITE setGamesCount NOTIFY gamesCountChanged)
    Q_PROPERTY(int gamesCompleteCount READ gamesCompleteCount WRITE setGamesCompleteCount NOTIFY gamesCompleteCountChanged)
    Q_PROPERTY(float cleanTime READ cleanTime WRITE setCleanTime NOTIFY cleanTimeChanged)

public:
    explicit GameProgress(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

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

signals:
    void currentGameIdChanged();
    void gamesCountChanged();
    void gamesCompleteCountChanged();
    void cleanTimeChanged();

};

#endif // GAMEPROGRESS_H
