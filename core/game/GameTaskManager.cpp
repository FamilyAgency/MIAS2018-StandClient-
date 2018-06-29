#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{    
    gamePreTask = new GamePreTask();
    taskCreator = new TaskCreator();
    gamePostTask = new GamePostTask();
    connect(gamePreTask, SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    connect(gamePreTask, SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));
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
    auto oneGameData = user->getCurrentGameData();
    currentUser = user;
    setupCurrentGame(oneGameData);
    setTaskState(TaskState::PreGame);
}

void GameTaskManager::stop()
{   
   // clearAllTasks();
    setTaskState(TaskState::None);
    emit taskReset();
}

void GameTaskManager::setupCurrentGame(const OneGameData& oneGameData)
{
    if(gameTask)
    {
        disconnect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
        disconnect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    }
    gameTask.clear();
    if(oneGameData.getId() != 3)
    {
        gameTask.reset(new GameTask(oneGameData.getPath(), oneGameData.getDifficult()));
        gameTask->setMindWaveClient(mindWave);
        connect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
        connect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    }

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
    gameTask->stop();
    auto completionTime = gameTask->getCompletionTime();
    emit taskComleteEvent(completionTime);
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

float GameTaskManager::getMindwaveLimit() const
{
    return gameTask->getMindwaveLimit();
}
