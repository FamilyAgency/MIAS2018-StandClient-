#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{
    gamePreTask = new GamePreTask();
    taskCreator = new TaskCreator();
    gamePostTask = new GamePostTask();
}

void GameTaskManager::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("gameTaskManager", this);
}

void GameTaskManager::setMindWaveClient(MindwaveComponent* value)
{
    mindWave = value;
}

void GameTaskManager::start(UserData* user)
{
    gameTasks = taskCreator->create(user);
    for(auto task: gameTasks)
    {
        task->setMindWaveClient(mindWave);
    }

    setAllTaskCount(gameTasks.length());
    setCurrentGameTaskIndex(0);
    setTaskState(TaskState::PreGame);
}

void GameTaskManager::stop()
{
    setAllTaskCount(gameTasks.length());
    setCurrentGameTaskIndex(0);
    setTaskState(TaskState::None);

    emit taskReset();
}

void GameTaskManager::setCurrentGameTaskIndex(int index)
{
    if(gameTask)
    {
        gameTask->stop();
    }

    gameTask = gameTasks[index];
    setCurrentTaskIndex(index);

    if(gameTask)
    {
        disconnect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
        disconnect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    }

    connect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    connect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));

    if(gamePreTask)
    {
        gamePreTask->stop();
    }

    if(gamePreTask)
    {
        disconnect(gamePreTask, SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
        disconnect(gamePreTask, SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));
    }
    connect(gamePreTask, SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    connect(gamePreTask, SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));

    emit taskNumberChangedEvent(index);
}

void GameTaskManager::setTaskState(TaskState taskState)
{  
    currentTaskState = taskState;
    switch(taskState)
    {
    case TaskState::None:
        emit updateCanvas();
        break;

    case TaskState::PreGame:
        gameTask->init();
        gamePreTask->init();
        gamePreTask->run();
        emit preTaskStartEvent();
        break;

    case TaskState::Game:
        gameTask->start();
        emit taskStartEvent();
        break;

    case TaskState::PostGame:
        break;
    }
}

void GameTaskManager::onPreGameTaskUpdate(float countDown)
{
    emit preTaskCoundownUpdate(countDown);
    emit updateCanvas();
}

void GameTaskManager::onPreGameTaskComplete()
{
    setTaskState(TaskState::Game);
}

void GameTaskManager::onTaskUpdateEvent()
{
    emit updateCanvas();
}

void GameTaskManager::onTaskCompleteEvent()
{
    auto completionTime = gameTask->getCompletionTime();

    if(!isAllTaskCompleted())
    {
        qDebug()<<this<<"-------------------------------onTaskCompleteEvent-------------------------------";
        setCurrentGameTaskIndex(currentTaskIndex() + 1);
        emit taskComleteEvent(completionTime);

        //save data
        //update data

        setTaskState(TaskState::PreGame);
    }
    else
    {
        emit taskComleteEvent(completionTime);
        emit allTaskComleteEvent();
        qDebug()<<this<<"------------------------------- Game Finished -------------------------------";
    }
}

bool GameTaskManager::isAllTaskCompleted() const
{
    return currentTaskIndex() == gameTasks.length() - 1;
}

bool GameTaskManager::isRunning() const
{
    return currentTaskState == TaskState::Game;
}

bool GameTaskManager::isPreTaskState() const
{
    return currentTaskState == TaskState::PreGame;
}

QPointF GameTaskManager::getStartPoint() const
{
    return gameTask->getStartPoint();
}

QPointF GameTaskManager::getCurPoint() const
{
    return gameTask->getCurPoint();
}

QPointF GameTaskManager::getEndPoint() const
{
    return gameTask->getEndPoint();
}

float GameTaskManager::getForwardVectorRotation() const
{
    return gameTask->getForwardVectorRotation();
}

QVariantList GameTaskManager::getCompletedPath() const
{
    return gameTask->getCompletedPath();
}

QVariantList GameTaskManager::getFullPath() const
{
    return gameTask->getFullPath();
}

int GameTaskManager::getTaskCount() const
{
    return gameTasks.length();
}

float GameTaskManager::getMindwaveLimit() const
{
    return gameTask->getMindwaveLimit();
}

void GameTaskManager::setCurrentTaskIndex(int value)
{
    _currentTaskIndex = value;
    emit currentTaskIndexChanged();
}

int GameTaskManager::currentTaskIndex() const
{
    return _currentTaskIndex;
}

void GameTaskManager::setAllTaskCount(int value)
{
    _allTaskCount = value;
    emit allTaskCountChanged();
}

int GameTaskManager::allTaskCount() const
{
    return _allTaskCount;
}
