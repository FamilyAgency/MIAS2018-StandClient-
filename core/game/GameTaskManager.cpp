#include "GameTaskManager.h"
#include <QDebug>
#include <QDateTime>

GameTaskManager::GameTaskManager()
{
    gameCountDown.reset(new GameCountDown());
    connect(gameCountDown.data(), SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    connect(gameCountDown.data(), SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));

    gameTask.reset(new GameTask());
    connect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    connect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    connect(gameTask.data(), SIGNAL(newCompletedPoint(const QPointF&)), this, SLOT(onNewCompletedPoint(const QPointF&)));
}

GameTaskManager::~GameTaskManager()
{
    disconnect(gameCountDown.data(), SIGNAL(update(float)), this, SLOT(onPreGameTaskUpdate(float)));
    disconnect(gameCountDown.data(), SIGNAL(complete()), this, SLOT(onPreGameTaskComplete()));

    disconnect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    disconnect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    disconnect(gameTask.data(), SIGNAL(newCompletedPoint(const QPointF&)), this, SLOT(onNewCompletedPoint(const QPointF&)));
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

void GameTaskManager::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}

void GameTaskManager::startGame()
{
    gameCompletedPath.clear();
    gameUncompletedPath = currentUser->getFullGamePath();
    targetPoints = currentUser->getTargetPoints();
    emit gameStarted();
}

void GameTaskManager::startStage()
{
    qDebug()<<"Game Started";
    auto game = currentUser->getCurrentStage();
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
        gameCountDown->stop();
        gameTask->stop();
        emit updateCanvas();
        break;

    case TaskState::PreGame:
        gameTask->init();
        gameCountDown->init();
        gameCountDown->run();
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
    gameUncompletedPath.pop_front();
    gameCompletedPath.append(point);
}

void GameTaskManager::onTaskCompleteEvent()
{
    gameTask->stop();
    targetPoints.pop_front();
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

QVector2D GameTaskManager::getForwardVector() const
{
    return gameTask->getForwardVector();
}

QVariantList GameTaskManager::getCompletedPath() const
{
    return gameCompletedPath;
}

QVariantList GameTaskManager::getGameUncompletedPath() const
{
    return gameUncompletedPath;
}

QVariantList GameTaskManager::getTargetPoints() const
{
    return targetPoints;
}

float GameTaskManager::getMindwaveLimit() const
{
    return gameTask->getMindwaveLimit();
}

QPointF GameTaskManager::getStartPoint1() const
{
    return currentUser->gameUserData().startPath[0];
}


QPointF GameTaskManager::getStartPoint2() const
{
   return currentUser->gameUserData().startPath[1];
}
