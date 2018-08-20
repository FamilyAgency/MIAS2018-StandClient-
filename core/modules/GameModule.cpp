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
    gameTaskManager->setUser(value);
}

void GameModule::setAdvantagesData(QSharedPointer<AdvantagesData> value)
{
    advantagesData = value;
}

void GameModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void GameModule::start()
{
    qDebug()<<"======================= GameModule START =======================";

    connectComponents();
    advantagesData->shuffle();
    gameTaskManager->startGame();
    startStage();
}

void GameModule::stop()
{ 
    qDebug()<<"======================= GameModule STOP =======================";

    disconnectComponents();
    gameTaskManager->stop();
}

void GameModule::startStage()
{
    gameTaskManager->startStage();
}

void GameModule::onStageComleteEvent(int completionTime)
{
    if(!currentUser->isFinalStage())
    {
        setCanContinue(false);
        dispatchAdvantageData();
        currentUser->currentStageCompleted(completionTime);
        serverComponent->updateGameRequest(currentUser->baseUserData().id);
    }
    else
    {
        currentUser->currentStageCompleted(completionTime);
        continueGame();
    }
    // gameSession->addTaskTime(completionTime);
}

void GameModule::dispatchAdvantageData()
{
    auto advantage = advantagesData->getNextAdvantage();
    QString advantageDescription = advantage.description;
    QString advantageTitle = advantage.title;
    QString videoPath = advantage.videoPath;
    QString advantageDescriptionMap = advantage.descriptionMap;
    emit stageComleteEvent(advantageTitle, advantageDescription, videoPath);
    emit stageComleteEventMap(advantageDescriptionMap);
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
            startStage();
        }
        else
        {
            auto descr = currentUser->gameUserData().descriptionWin;
            auto imageWinName = currentUser->gameUserData().imageWinName;
            emit allStagesComleteEventMap(descr, imageWinName);
            emit allStagesComleteEvent();

            gameTaskManager->stop();
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


