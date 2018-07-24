#include "AppController.h"
#include "components/mindwave/tcp/MindwaveComponentTCP.h"
#include "components/mindwave/serial/MindwaveComponentSerial.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    //createEngine<RFIDComponent, MindwaveComponentTest>();
}

template <class RFIDComponentT, class MindwaveComponentT>
void AppController::createEngine()
{
    appSettings.reset(new AppSettings);
    appSettings->init();

    userData.reset(new UserData());
    standData.reset(new StandData());
    gameSession.reset(new GameSession());

    //////////////////// components //////////////////////

    loggerComponent.reset(new LoggerComponent());
    components.append(loggerComponent);

    rfidComponent.reset(new RFIDComponentT());
    components.append(rfidComponent);

    mindWaveComponent.reset(new MindwaveComponentT());
    components.append(mindWaveComponent);

    serverComponent.reset(new ServerRemoteComponent());
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

    modules.append(introModule);

    instructionModule.reset(new InstructionModule());
    modules.append(instructionModule);

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
    modules.append(gameResultModule);

    superGameModule.reset(new SuperGameModule());
    superGameModule->setUser(userData);
    superGameModule->setServerComponent(serverComponent);
    connect(superGameModule.data(), SIGNAL(superGameFailed()), this, SLOT(onSuperGameFailed()));
    connect(superGameModule.data(), SIGNAL(superGameSuccess(int)), this, SLOT(onSuperGameSuccess(int)));

    modules.append(superGameModule);

    superGameResultModule.reset(new SuperGameResultModule());
    modules.append(superGameResultModule);
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
}

void AppController::onConfigLoaded(ConfigPtr config)
{
    if(config->mindwaveConfig->type == "simulation")
    {
        qDebug()<<"Mindwave simulation true";
        createEngine<RFIDComponent, MindwaveComponentTest>();
    }
    else if(config->mindwaveConfig->type == "tcp")
    {
        qDebug()<<"Mindwave simulation false";
        createEngine<RFIDComponent, MindwaveComponentTCP>();
    }
    else if(config->mindwaveConfig->type == "serial")
    {
        qDebug()<<"Mindwave simulation false";
        createEngine<RFIDComponent, MindwaveComponentSerial>();
    }

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

    bool build = false;

    if(build)
    {
        setAppState(AppState::Intro);
    }
    else
    {
        // userData->setGameCategory(1);
        setAppState(AppState::Intro);
    }
}

void AppController::onServerResponse(const ServerResponse& response)
{

}

void AppController::onUserStartPlay()
{
    gameSession->start();
}

void AppController::onGameCategoryUpdate(int id)
{
    userData->setGameCategory(id);
}

void AppController::onCarStarting()
{
    startGame();
}

void AppController::onAllTaskComleteEvent()
{
    setAppState(AppState::GameResult);
}

void AppController::onSuperGameFailed()
{
    setAppState(AppState::SuperGameResult);
}

void AppController::onSuperGameSuccess(int time)
{
    setAppState(AppState::SuperGameResult);
}

void AppController::startInstruction()
{
    setAppState(AppState::Instruction);
}

void AppController::startRoulette()
{
    setAppState(AppState::Roulette);
}

void AppController::startGame()
{
    setAppState(AppState::Game);
}

void AppController::startGameResult()
{
    setAppState(AppState::GameResult);
}

void AppController::startSuperGame()
{
    setAppState(AppState::SuperGame);
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

