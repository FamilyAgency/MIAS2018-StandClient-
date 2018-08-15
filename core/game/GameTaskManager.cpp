#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{    
    gamePreTask = new GamePreTask();
    gamePostTask = new GamePostTask();

    connect(gamePreTask, SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    connect(gamePreTask, SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));

    gameTask.reset(new GameTask());
    connect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    connect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    connect(gameTask.data(), SIGNAL(newCompletedPoint(const QPointF&)), this, SLOT(onNewCompletedPoint(const QPointF&)));


}

void GameTaskManager::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("gameTaskManager", this);
}

void GameTaskManager::setMindWaveClient(QSharedPointer<MindwaveComponentBase> value)
{
    mindWave = value;
    gameTask->setMindWaveClient(mindWave);
}

void GameTaskManager::startGame()
{
      gameCompletedPath.clear();
}

void GameTaskManager::startStage(QSharedPointer<UserData> user)
{
    qDebug()<<"Game Started";
    auto game = user->getCurrentStage();
    currentUser = user;  
    setupCurrentGame(game);    

    setTaskState(TaskState::PreGame);
}

void GameTaskManager::stop()
{
    setTaskState(TaskState::None);
    emit taskReset();
}

void GameTaskManager::setupCurrentGame(const OneStageData& oneStageData)
{
    gameTask->setData(oneStageData.getPath(), oneStageData.getDifficult());
}

void GameTaskManager::setTaskState(TaskState taskState)
{  
    currentTaskState = taskState;  

    switch(taskState)
    {
    case TaskState::None:
        gamePreTask->stop();
        gameTask->stop();
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

void GameTaskManager::onNewCompletedPoint(const QPointF& point)
{
    gameCompletedPath.append(point);
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
    return gameCompletedPath;
}

QVariantList GameTaskManager::getFullGamePath() const
{    
    return currentUser->getFullGamePath();
}

QVariantList GameTaskManager::getTargetPoints() const
{
    return currentUser->getTargetPoints();
}

float GameTaskManager::getMindwaveLimit() const
{
    return gameTask->getMindwaveLimit();
}
