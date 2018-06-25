#ifndef GAMETASKMANAGER_H
#define GAMETASKMANAGER_H

#include <QObject>
#include <QList>
#include <QTimer>
#include <QVariantList>
#include "components/MindwaveComponent.h"

#include "core/game/GameTask.h"
#include "core/game/GamePreTask.h"
#include "core/game/GamePostTask.h"

#include "core/game/TaskCreator.h"

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
    Q_INVOKABLE int getTaskCount() const;
    Q_INVOKABLE float getMindwaveLimit() const;

    Q_PROPERTY(int currentTaskIndex READ currentTaskIndex WRITE setCurrentTaskIndex NOTIFY currentTaskIndexChanged)
    Q_PROPERTY(int allTaskCount READ allTaskCount WRITE setAllTaskCount NOTIFY allTaskCountChanged)

    void setCurrentTaskIndex(int value);
    int currentTaskIndex() const;

    void setAllTaskCount(int value);
    int allTaskCount() const;

    enum class TaskState
    {
        None,
        PreGame,
        Game,
        PostGame
    };

    void start();
    void stop();
    void setMindWaveClient(MindwaveComponent* mindWave);
    void setTaskState(TaskState taskState);

private:
    TaskState currentTaskState;
    TaskCreator* taskCreator;
    MindwaveComponent* mindWave = nullptr;

    void runTask();
    void preTaskTimerComplete();
    void setCurrentGameTaskIndex(int index);
    void initCurrentTask();
    bool isAllTaskCompleted() const;

    GamePreTask* gamePreTask = nullptr;
    GameTask* gameTask = nullptr;
    GamePostTask* gamePostTask = nullptr;
    QList<GameTask*> gameTasks;

    int _currentTaskIndex = 1;
    int _allTaskCount = 1;

signals:
    void updateCanvas();
    void gameTimeChanged();
    void taskComleteEvent(int completionTime);
    void allTaskComleteEvent();

    void taskStartEvent();
    void preTaskStartEvent();
    void taskNumberChangedEvent(int taskNumber);
    void preTaskCoundownUpdate(float time);

    void currentTaskIndexChanged();
    void allTaskCountChanged();
    void taskReset();

private slots:
    void onTaskCompleteEvent();
    void onPreGameTaskUpdate(float countDown);
    void onPreGameTaskComplete();
    void onTaskUpdateEvent();
};

#endif // GAMETASKMANAGER_H
