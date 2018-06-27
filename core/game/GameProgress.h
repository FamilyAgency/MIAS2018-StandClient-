#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QVector>
#include "OneGameData.h"

class GameProgress : public QObject
{
    Q_OBJECT
public:
    explicit GameProgress(QObject *parent = nullptr);

    void setCurrentStage(int stage);
    void setGames(const QVector<OneGameData>& data);
    void setStageCompletionTime(float time);

    QVector<OneGameData> getGames() const;

private:
    QVector<OneGameData> gamesData;
    int currentStage;
    float complitionTime;


signals:

public slots:
};

#endif // GAMEPROGRESS_H
