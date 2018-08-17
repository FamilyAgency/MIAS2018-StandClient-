#include "AppController.h"
#include "components/mindwave/tcp/MindwaveComponentTCP.h"
#include "components/mindwave/serial/MindwaveComponentSerial.h"

#include "components/rfid/ACR122CardHandler.h"
#include "components/server/ServerRemoteComponent.h"
#include "tests/ServerRemoteComponentTest.h"

AppController::AppController(QObject *parent) : QObject(parent)
{

}

template <class MindwaveComponentT>
void AppController::createMindwave()
{
    mindWaveComponent.reset(new MindwaveComponentT());
    components.append(mindWaveComponent);
}

template <class RFIDComponentT>
void AppController::createRFID()
{
    rfidComponent.reset(new RFIDComponentT());
    components.append(rfidComponent);
}

void AppController::createEngine()
{
    appSettings.init();

    userData.reset(new UserData());
    standData.reset(new StandData());
    dilerData.reset(new DilerData());
    gameSession.reset(new GameSession());

    //////////////////// components //////////////////////

    loggerComponent.reset(new LoggerComponent());
    components.append(loggerComponent);

    //ServerRemoteComponent
    serverComponent.reset(new ServerRemoteComponentTest());
    connect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    components.append(serverComponent);

    healthCheckerComponent.reset(new HealthCheckerComponent());
    healthCheckerComponent->addComponent(rfidComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);

    monitoringComponent.reset(new MonitoringComponent());
    components.push_back(monitoringComponent);

    ////////////////////// modules //////////////////////

    introModule.reset(new IntroModule());
    introModule->setRFIDComponent(rfidComponent);
    introModule->setUserData(userData);
    introModule->setServerComponent(serverComponent);
    introModule->setStandData(standData);
    connect(introModule.data(), SIGNAL(userStartPlay()), this, SLOT(onUserStartPlay()));
    connect(introModule.data(), SIGNAL(userAcceptedGame()), this, SLOT(onUserAcceptedGame()));

    modules.append(introModule);

    instructionModule.reset(new InstructionModule());
    modules.append(instructionModule);
    connect(instructionModule.data(), SIGNAL(instructionComplete()), this, SLOT(onInstructionComplete()));
    

    rouletteModule.reset(new RouletteModule());
    rouletteModule->setMindwave(mindWaveComponent);
    rouletteModule->setServerComponent(serverComponent);
    rouletteModule->setUser(userData);

    connect(rouletteModule.data(), SIGNAL(gameCategoryUpdate(int)), this, SLOT(onGameCategoryUpdate(int)));
    connect(rouletteModule.data(), SIGNAL(carStarting()), this, SLOT(onCarStarting()));

    modules.append(rouletteModule);

    gameModule.reset(new GameModule());
    gameModule->setMindwave(mindWaveComponent);
    gameModule->setGameSession(gameSession);
    gameModule->setUser(userData);
    gameModule->setServerComponent(serverComponent);
    connect(gameModule.data(), SIGNAL(allStagesComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
    modules.append(gameModule);

    gameResultModule.reset(new GameResultModule());
    connect(gameResultModule.data(), SIGNAL(superGameAccepted()), this, SLOT(onSuperGameAccepted()));
    connect(gameResultModule.data(), SIGNAL(superGameRejected()), this, SLOT(onSuperGameRejected()));
    modules.append(gameResultModule);

    superGameModule.reset(new SuperGameModule());
    superGameModule->setUser(userData);
    superGameModule->setServerComponent(serverComponent);
    superGameModule->setMindWaveClient(mindWaveComponent);
    connect(superGameModule.data(), SIGNAL(superGameFailed()), this, SLOT(onSuperGameFailed()));
    connect(superGameModule.data(), SIGNAL(superGameSuccess(int)), this, SLOT(onSuperGameSuccess(int)));

    modules.append(superGameModule);

    superGameResultModule.reset(new SuperGameResultModule());
    connect(superGameResultModule.data(), SIGNAL(superGameResultReaded()), this, SLOT(onSuperGameResultReaded()));

    modules.append(superGameResultModule);

    testDriveModule.reset(new TestDriveModule());
    testDriveModule->setServerComponent(serverComponent);
    testDriveModule->setUser(userData);
    testDriveModule->setDilerData(dilerData);
    modules.append(testDriveModule);

    animationManager.reset(new AnimationManager());
}

AppController::~AppController()
{
    disconnect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));

    disconnect(rouletteModule.data(), SIGNAL(gameCategoryUpdate(int)), this, SLOT(onGameCategoryUpdate(int)));
    disconnect(rouletteModule.data(), SIGNAL(carStarting()), this, SLOT(onCarStarting()));

    disconnect(gameModule.data(), SIGNAL(allStagesComleteEvent()), this, SLOT(onAllTaskComleteEvent()));

    disconnect(superGameModule.data(), SIGNAL(superGameFailed()), this, SLOT(onSuperGameFailed()));
    disconnect(superGameModule.data(), SIGNAL(superGameSuccess(int)), this, SLOT(onSuperGameSuccess(int)));

    disconnect(introModule.data(), SIGNAL(userStartPlay()), this, SLOT(onUserStartPlay()));
    disconnect(introModule.data(), SIGNAL(userAcceptedGame()), this, SLOT(onUserAcceptedGame()));

    disconnect(instructionModule.data(), SIGNAL(instructionComplete()), this, SLOT(onInstructionComplete()));

    disconnect(gameResultModule.data(), SIGNAL(superGameAccepted()), this, SLOT(onSuperGameAccepted()));
    disconnect(gameResultModule.data(), SIGNAL(superGameRejected()), this, SLOT(onSuperGameRejected()));

    disconnect(superGameResultModule.data(), SIGNAL(superGameResultReaded()), this, SLOT(onSuperGameResultReaded()));
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{
    for (auto module : modules)
    {
        module->setQmlContext(qmlContext);
    }

    for (auto comp : components)
    {
        comp->setQmlContext(qmlContext);
    }

    userData->setQmlContext(qmlContext);
    standData->setQmlContext(qmlContext);
    gameSession->setQmlContext(qmlContext);

    animationManager->setQmlContext(qmlContext);
}

void AppController::onConfigLoaded(ConfigPtr config)
{
    if(config->mindwaveConfig->type == "simulation")
    {
        qDebug()<<"Mindwave simulation true";
        createMindwave<MindwaveComponentTest>();
    }
    else if(config->mindwaveConfig->type == "tcp")
    {
        qDebug()<<"Mindwave simulation false";
        createMindwave<MindwaveComponentTCP>();
    }
    else if(config->mindwaveConfig->type == "serial")
    {
        qDebug()<<"Mindwave simulation false";
        createMindwave<MindwaveComponentSerial>();
    }

    createRFID<ACR122CardHandler>();
    createEngine();

    for (auto comp : components)
    {
        comp->setConfig(config);
    }

    for (auto module : modules)
    {
        module->setConfig(config);
    }

    standData->setConfig(config);
    userData->setConfig(config);
    
    animationManager->setConfig(config);
    
    start();
}

void AppController::start()
{
    qDebug()<<"============================================";
    qDebug()<<"============================================";
    qDebug()<<"============================================";
    QString message = "======================APP STARTED ======================";
    loggerComponent->log(message, LogType::Verbose, LogRemoteType::Slack, true);

    for (auto comp : components)
    {
        comp->start();
    }

    setAppState(AppState::Intro);
}

void AppController::onServerResponse(const ServerResponse& response)
{

}

// ============== Intro Module ============== //

void AppController::onUserStartPlay()
{
    gameSession->start();
}

void AppController::onUserAcceptedGame()
{
    setAppState(AppState::Instruction);
}


// ============== Instruction Module ============== //


void AppController::onInstructionComplete()
{
    setAppState(AppState::Roulette);
}

// ============== Roulette Module ============== //

void AppController::onGameCategoryUpdate(int id)
{
    userData->setGameCategory(id);
}

void AppController::onCarStarting()
{
    startGame();
}

void AppController::startGame()
{
    setAppState(AppState::Game);
}

// ============== Game Module ============== //

void AppController::onAllTaskComleteEvent()
{
    setAppState(AppState::GameResult);
}

// ============== Game Result Module ============== //

void AppController::onSuperGameAccepted()
{
    setAppState(AppState::SuperGame);
}

void AppController::onSuperGameRejected()
{
    backToIntro();
}

// ============== Super Game Module ============== //

void AppController::onSuperGameFailed()
{
    setAppState(AppState::SuperGameResult);
}

void AppController::onSuperGameSuccess(int time)
{
    setAppState(AppState::SuperGameResult);
}

// ============== Super Game Result Module ============== //
void AppController::onSuperGameResultReaded()
{
    setAppState(AppState::TestDrive);
}

void AppController::backToIntro()
{
    gameSession->stop();
    userData->clearData();
    setAppState(AppState::Intro);
}

void AppController::setAppState(AppState value)
{
    if(currentModule)
    {
        currentModule->stop();
    }

    appState = value;

    currentModule = getModuleByAppState(value);

    currentModule->start();
    emit appStateChanged(value);

    QString message = "___App state changed : " + currentModule->getName();
    loggerComponent->log(message, LogType::Verbose, LogRemoteType::Slack, true);
}

AppController::AppState AppController::getAppState() const
{
    return appState;
}

QSharedPointer<BaseModule> AppController::getModuleByAppState(AppState value)
{
    switch(value)
    {
    case AppState::Intro: return introModule;
    case AppState::Instruction: return instructionModule;
    case AppState::Roulette: return rouletteModule;
    case AppState::Game: return gameModule;
    case AppState::GameResult: return gameResultModule;
    case AppState::SuperGame: return superGameModule;
    case AppState::SuperGameResult: return superGameResultModule;
    case AppState::TestDrive: return testDriveModule;
    }

    return nullptr;
}

void AppController::onConfigError(const QString& errorMessage)
{
    qDebug() << "config Service Error";

    emit configError(errorMessage);
}

//===================TESTS===================

void AppController::testCrash()
{  
    IntroModule* module;
    module->start();
}

void AppController::setAppStateTest(AppState appState)
{
    if(appState == AppState::Game)
    {
        userData->setGameCategory(0);
    }

    setAppState(appState);
}

void AppController::setTestUserId(int id)
{
    BaseUserData baseUserData;
    baseUserData.id = id;
    userData->setBaseUserData(baseUserData);
}




