#ifndef GAMETASKMANAGER_H
#define GAMETASKMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QVariantList>
#include "components/mindwave/MindwaveComponentBase.h"

#include "core/game/GameTask.h"
#include "core/game/GamePreTask.h"
#include "core/game/GamePostTask.h"

#include "core/data/UserData.h"

class GameTaskManager: public QObject
{
    Q_OBJECT
public:
    GameTaskManager();

    Q_INVOKABLE bool isRunning() const;
    Q_INVOKABLE bool isPreTaskState() const;
    Q_INVOKABLE QPointF getStartPoint() const;    
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE QPointF getEndPoint() const;
    Q_INVOKABLE QVariantList getCompletedPath() const;
    Q_INVOKABLE QVariantList getFullPath() const;
    Q_INVOKABLE float getForwardVectorRotation() const;
    Q_INVOKABLE float getMindwaveLimit() const;

    enum class TaskState
    {
        None,
        PreGame,
        Game,
        PostGame
    };

    void start(QSharedPointer<UserData> value);
    void stop();
    void setMindWaveClient(QSharedPointer<MindwaveComponentBase> mindWave);
    void setTaskState(TaskState taskState);
    void setQmlContext(QQmlContext* value);

private:
    TaskState currentTaskState;
    QSharedPointer<MindwaveComponentBase> mindWave = nullptr;

    void runTask();
    void preTaskTimerComplete();
    void setupCurrentGame(const OneStageData& gameData);
    void initCurrentTask();

    GamePreTask* gamePreTask = nullptr;
    QSharedPointer<GameTask> gameTask = nullptr;
    GamePostTask* gamePostTask = nullptr;

    int currentGameId = 0;
    QSharedPointer<UserData> currentUser;

signals:
    void updateCanvas();   
    void taskComleteEvent(int completionTime);
   // void allTaskComleteEvent();

    void taskStartEvent();
    void preTaskStartEvent();  
    void preTaskCoundownUpdate(float time);
    void taskReset();

private slots:
    void onTaskCompleteEvent();
    void onPreGameTaskUpdate(float countDown);
    void onPreGameTaskComplete();
    void onTaskUpdateEvent();
};

#endif // GAMETASKMANAGER_H
