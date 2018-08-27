#ifndef GAMETASKMANAGER_H
#define GAMETASKMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QVariantList>
#include "components/mindwave/MindwaveComponentBase.h"

#include "core/game/GameTask.h"
#include "core/game/GameCountDown.h"

#include "core/data/UserData.h"

class GameTaskManager: public QObject
{
    Q_OBJECT
public:
    GameTaskManager();
    ~GameTaskManager();

    Q_INVOKABLE bool isRunning() const;
    Q_INVOKABLE bool isPreTaskState() const;
    Q_INVOKABLE QPointF getStartPoint() const;    
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE QPointF getEndPoint() const;
    Q_INVOKABLE QVariantList getCompletedPath() const;
    Q_INVOKABLE QVariantList getGameUncompletedPath() const;
    Q_INVOKABLE QVariantList getTargetPoints() const;
    Q_INVOKABLE float getForwardVectorRotation() const;
    Q_INVOKABLE QVector2D getForwardVector() const;
    Q_INVOKABLE float getMindwaveLimit() const;

    Q_INVOKABLE QPointF getStartPoint1() const;
    Q_INVOKABLE QPointF getStartPoint2() const;

    enum class TaskState
    {
        None,
        PreGame,
        Game,
        PostGame
    };
    void startGame();
    void startStage();
    void stop();
    void setMindWaveClient(QSharedPointer<MindwaveComponentBase> mindWave);
    void setTaskState(TaskState taskState);
    void setQmlContext(QQmlContext* value);
    void setUser(QSharedPointer<UserData> value);

private:
    TaskState currentTaskState;
    QSharedPointer<MindwaveComponentBase> mindWave = nullptr;

    void runTask();
    void preTaskTimerComplete();
    void setupCurrentGame(const OneStageData& gameData);
    void initCurrentTask();

    QSharedPointer<GameCountDown> gameCountDown = nullptr;
    QSharedPointer<GameTask> gameTask = nullptr;

    int currentGameId = 0;
    QSharedPointer<UserData> currentUser;

    QVariantList gameCompletedPath, gameUncompletedPath, targetPoints;

signals:
    void updateCanvas();   
    void taskComleteEvent(int completionTime);
    void taskStartEvent();
    void preTaskStartEvent();  
    void preTaskCoundownUpdate(float time);
    void taskReset();
    void gameStarted();

private slots:
    void onTaskCompleteEvent();
    void onPreGameTaskUpdate(float countDown);
    void onPreGameTaskComplete();
    void onTaskUpdateEvent();
    void onNewCompletedPoint(const QPointF& point);

};

#endif // GAMETASKMANAGER_H
