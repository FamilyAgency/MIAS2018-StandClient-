#include "GameModule.h"

GameModule::GameModule() : BaseModule()
{
   gameTaskManager.reset(new GameTaskManager);
   connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onTaskComleteEvent(int)));
   connect(gameTaskManager.data(), SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
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
    gameTaskManager->setQmlContext(value);
}

void GameModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);   
}

void GameModule::start()
{ 
    gameTaskManager->start();
}

void GameModule::stop()
{ 
   gameTaskManager->stop();
}

void GameModule::onTaskComleteEvent(int completionTime)
{
    gameSession->addTaskTime(completionTime);
}

void GameModule::onAllTaskComleteEvent()
{
   emit allTaskComleteEvent();
}

QString GameModule::getName() const
{
    return "Game location";
}



