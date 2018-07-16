#include "GameModule.h"

GameModule::GameModule(QObject *parent):BaseModule(parent)
{
    gameTaskManager.reset(new GameTaskManager);
    connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onTaskComleteEvent(int)));
}

GameModule::~GameModule()
{

}

void GameModule::setMindwave(QSharedPointer<MindwaveComponent> value)
{
    mindWaveComponent = value;
    gameTaskManager->setMindWaveClient(mindWaveComponent);
}

void GameModule::setGameSession(QSharedPointer<GameSession> value)
{
    gameSession = value;
}

void GameModule::setQmlContext(QQmlContext* value)
{
    BaseModule::setQmlContext(value);
    qmlContext->setContextProperty("gameModule", this);
    gameTaskManager->setQmlContext(value);
}

void GameModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void GameModule::start()
{     
    gameTaskManager->start(currentUser);
}

void GameModule::stop()
{ 
    gameTaskManager->stop();
}

void GameModule::onTaskComleteEvent(int completionTime)
{
    const float toSeconds = 1/1000.0f;
    currentUser->currentGameCompleted(completionTime * toSeconds);
    gameSession->addTaskTime(completionTime);

    //if(currentUser->hasGames())
   // {
       // start();
       emit taskComleteEvent();
   // }

}

void GameModule::continueGame()
{
    if(currentUser->hasGames())
    {
       start();
    }
    else
    {
        emit allTaskComleteEvent();
    }
}

void GameModule::onAllTaskComleteEvent()
{
    emit allTaskComleteEvent();
}

QString GameModule::getName() const
{
    return "Game location";
}

void GameModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}
