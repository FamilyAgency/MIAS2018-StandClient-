#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QVector>
#include <QQmlContext>
#include "OneGameData.h"

class GameProgress : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int currentStage READ currentStage WRITE setCurrentStage NOTIFY currentStageChanged)
    Q_PROPERTY(int gamesCount READ gamesCount WRITE setGamesCount NOTIFY gamesCountChanged)
    Q_PROPERTY(int gamesCompleteCount READ gamesCompleteCount WRITE setGamesCompleteCount NOTIFY gamesCompleteCountChanged)
    Q_PROPERTY(float cleanTime READ cleanTime WRITE setCleanTime NOTIFY cleanTimeChanged)

public:
    explicit GameProgress(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    void setCurrentStage(int stage);
    int currentStage() const;

    void setGamesCount(int count);
    int gamesCount() const;

    void setGamesCompleteCount(int count);
    int gamesCompleteCount() const;

    void setCleanTime(float count);
    float cleanTime() const;

    void setGames(const QVector<OneGameData>& data);
    void setStageCompletionTime(float time);

    QVector<OneGameData> getGames() const;

private:
    QVector<OneGameData> gamesData;
    int _currentStage = 0;
    int _gamesCount = 0;
    int _gamesCompleteCount = 0;
    float complitionTime;
    float _cleanTime = 0.0f;

signals:
    void currentStageChanged();
    void gamesCountChanged();
    void gamesCompleteCountChanged();
    void cleanTimeChanged();

};

#endif // GAMEPROGRESS_H
