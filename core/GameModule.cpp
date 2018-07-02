#include "GameModule.h"

GameModule::GameModule() : BaseModule()
{
    gameTaskManager.reset(new GameTaskManager);
    connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onTaskComleteEvent(int)));
}

void GameModule::setMindwave(MindwaveComponent* value)
{
    mindWaveComponent = value;
    gameTaskManager->setMindWaveClient(mindWaveComponent);
}

void GameModule::setGameSession(GameSession* value)
{
    gameSession = value;
}

void GameModule::setQmlContext(QQmlContext* value)
{
    BaseModule::setQmlContext(value);
    qmlContext->setContextProperty("gameModule", this);
    gameTaskManager->setQmlContext(value);
}

void GameModule::setConfig(Config* config)
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

void GameModule::setUser(UserData* value)
{
    currentUser = value;
}
