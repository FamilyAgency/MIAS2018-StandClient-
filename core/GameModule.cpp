#include "GameModule.h"

GameModule::GameModule() : BaseModule()
{
   mindWave.reset(new MindwaveComponent);

   gameTaskManager.reset(new GameTaskManager);
   gameTaskManager->setMindWaveClient(mindWave.data());
   connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onTaskComleteEvent(int)));
   connect(gameTaskManager.data(), SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
}

void GameModule::setGameSession(GameSession* value)
{
    gameSession = value;
}

void GameModule::setQmlContext(QQmlContext* value)
{
    BaseModule::setQmlContext(value);

    qmlContext->setContextProperty("mind", mindWave.data());   
    qmlContext->setContextProperty("gameTaskManager", gameTaskManager.data());
    qmlContext->setContextProperty("gameSession", gameSession);
}

void GameModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
    mindWave->setConfig(config->mindwaveConfig);
}

void GameModule::start()
{
   // gameSession->start();
    gameTaskManager->start();
}

void GameModule::stop()
{
    gameTaskManager->stop();
    //gameSession->stop();
}

void GameModule::onTaskComleteEvent(int completionTime)
{
    gameSession->addTaskTime(completionTime);
}

void GameModule::onAllTaskComleteEvent()
{
   emit allTaskComleteEvent();
}



