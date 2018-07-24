#include "GameModule.h"

GameModule::GameModule(QObject *parent):BaseModule(parent)
{
    gameTaskManager.reset(new GameTaskManager);
    connect(gameTaskManager.data(), SIGNAL(taskComleteEvent(int)), this, SLOT(onStageComleteEvent(int)));
}

GameModule::~GameModule()
{

}

void GameModule::setMindwave(QSharedPointer<MindwaveComponentBase> value)
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
    qDebug()<<"======================= GameModule START =======================";

    connectComponents();
    startGame();
}

void GameModule::stop()
{ 
    qDebug()<<"======================= GameModule STOP =======================";

    disconnectComponents();
    gameTaskManager->stop();
}

void GameModule::startGame()
{
     gameTaskManager->start(currentUser);
}

void GameModule::onStageComleteEvent(int completionTime)
{
    setCanContinue(false);
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

void GameModule::onUserUpdatedGame()
{
    setCanContinue(true);
}

void GameModule::continueGame()
{
    if(canContinue())
    {
        if(currentUser->hasStages())
        {
           startGame();
        }
        else
        {
            emit allStagesComleteEvent();
        }
    }
}

QString GameModule::getName() const
{
    return "Game location";
}

bool GameModule::canContinue() const
{
    return _canContinue;
}

void GameModule::setCanContinue(bool value)
{
    _canContinue = value;
    emit canContinueChanged();
}

void GameModule::connectComponents()
{
    if(serverComponent)
    {
        connect(serverComponent.data(), SIGNAL(userUpdatedGame()), this, SLOT(onUserUpdatedGame()));
    }
}

void GameModule::disconnectComponents()
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(userUpdatedGame()), this, SLOT(onUserUpdatedGame()));
    }
}


