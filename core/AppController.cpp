#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    testConstruct();
    //releaseConstruct();
}

void AppController::testConstruct()
{
    userData = new UserData();
    standData = new StandData();
    gameSession = new GameSession();

    ////////////////////// components //////////////////////

    logger = new LoggerComponent();
    components.append(logger);

    rfidComponent = new RFIDComponent();
    components.append(rfidComponent);

    mindWaveComponent = new MindwaveComponentTest();
    components.append(mindWaveComponent);

    serverComponent = new ServerComponentTest();
    components.append(serverComponent);    

    healthCheckerComponent = new HealthCheckerComponent();
    healthCheckerComponent->addComponent(rfidComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);   

    ////////////////////// modules //////////////////////

    introModule = new IntroModuleTest();
    connect(introModule, SIGNAL(loginStateChanged(LoginState)), this, SLOT(onLoginStateChanged(LoginState)));

    introModule->setRFIDComponent(rfidComponent);
    introModule->setUserData(userData);
    introModule->setServerComponent(serverComponent);
    introModule->setStandData(standData);
    modules.append(introModule);

    instructionModule = new InstructionModule();
    modules.append(instructionModule);

    gameModule = new GameModule();
    gameModule->setMindwave(mindWaveComponent);
    gameModule->setGameSession(gameSession);
    connect(gameModule, SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
    modules.append(gameModule);

    resultModule = new ResultModule();
    modules.append(resultModule);
}

void AppController::releaseConstruct()
{

}

void AppController::onLoginStateChanged(LoginState loginState)
{
    //QString loginMsg = "login state changed  " + loginModule->getStringState();
    //logger->log(loginMsg);

    if(loginState == LoginState::Login)
    {
        gameModule->setUser(userData);
        gameSession->start();
    }
    else if(loginState == LoginState::Logout)
    {
        userData->clearData();
        gameSession->stop();
        setAppState(AppState::Login);
    }
}

void AppController::onAllTaskComleteEvent()
{
    setAppState(AppState::Result);
}

void AppController::startInstruction()
{
    setAppState(AppState::Instruction);
}

void AppController::startGame()
{
    setAppState(AppState::Game);
}

void AppController::startResult()
{
    setAppState(AppState::Result);
}

void AppController::setQmlContext(QQmlContext* qmlContext)
{    
    for (auto comp : components)
    {
        comp->setQmlContext(qmlContext);
    }

    userData->setQmlContext(qmlContext);
    standData->setQmlContext(qmlContext);
    gameSession->setQmlContext(qmlContext);

    for (auto module : modules)
    {
        module->setQmlContext(qmlContext);
    }
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

    //logger->log("App state changed : " + currentModule->getName(), LogType::Verbose, LoggerService::RemoteType::Slack);
}

BaseModule* AppController::getModuleByAppState(AppState value)
{
    switch(value)
    {
    case AppState::Login: return introModule;
    case AppState::Instruction: return instructionModule;
    case AppState::Game: return gameModule;
    case AppState::Result: return resultModule;
    }

    return nullptr;
}

void AppController::onConfigLoaded(ConfigPtr config)
{
    for (auto comp : components)
    {
        comp->setConfig(config);
    }

    for (auto module : modules)
    {
        module->setConfig(config);
    }

    standData->setConfig(config);

   // start();
}

void AppController::onConfigError()
{
    qDebug() << "config Service Error";
}

void AppController::start()
{    
   // QString initStatus = "Stand " + QString::number(standData->config().appId) + " started.........";
    //logger->log(initStatus, LogType::Verbose, LoggerService::RemoteType::Slack);

    for (auto comp : components)
    {
        comp->start();
    }

    setAppState(AppState::Login);
}

void AppController::backtoIntro()
{
    setAppState(AppState::Login);
}


