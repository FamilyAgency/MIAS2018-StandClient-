#include "GameModule.h"

GameModule::GameModule(QObject *parent):BaseModule(parent)
{
    gameTaskManager.reset(new GameTaskManager);
    connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onStageComleteEvent(int)));
}

GameModule::~GameModule()
{

}

void GameModule::setMindwave(QSharedPointer<MindwaveComponent> value)
{
    mindWaveComponent = value;
    gameTaskManager->setMindWaveClient(mindWaveComponent);
}

void GameModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
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

void GameModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
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

void GameModule::onStageComleteEvent(int completionTime)
{
    dispatchAdvantageData();
    currentUser->currentStageCompleted(completionTime);
    serverComponent->updateGameRequest(currentUser->baseUserData().id);
   // gameSession->addTaskTime(completionTime);
}

void GameModule::dispatchAdvantageData()
{
    auto userGameData = currentUser->getCurrentStage();
    QString advantageDescription = userGameData.getAdvantage().description;
    QString advantageTitle = userGameData.getAdvantage().title;
    QString videoPath = userGameData.getAdvantage().videoPath;
    emit stageComleteEvent(advantageTitle, advantageDescription, videoPath);
}

void GameModule::continueGame()
{
    if(currentUser->hasStages())
    {
        start();
    }
    else
    {
        emit allStagesComleteEvent();
    }
}

QString GameModule::getName() const
{
    return "Game location";
}


