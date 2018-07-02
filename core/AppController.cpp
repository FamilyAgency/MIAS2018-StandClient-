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

    rfidComponent = new RFIDComponent();
    components.append(rfidComponent);

    mindWaveComponent = new MindwaveComponentTest();
    components.append(mindWaveComponent);

    serverComponent = new ServerComponentTest();
    components.append(serverComponent);

    slackComponent = new SlackComponent();
    components.append(slackComponent);

    healthCheckerComponent = new HealthCheckerComponent();
    healthCheckerComponent->addComponent(rfidComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);

    loginModule = new LoginModuleTest();
    connect(loginModule, SIGNAL(loginStateChanged(LoginModule::LoginState)), this, SLOT(onLoginStateChanged(LoginModule::LoginState)));

    loginModule->setRFIDComponent(rfidComponent);
    loginModule->setUserData(userData);
    loginModule->setServerComponent(serverComponent);
    loginModule->setStandData(standData);
    modules.append(loginModule);

    instructionModule = new InstructionModule();
    modules.append(instructionModule);

    gameModule = new GameModule();
    gameModule->setMindwave(mindWaveComponent);
    gameModule->setGameSession(gameSession);
    connect(gameModule, SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
    modules.append(gameModule);

    resultModule = new ResultModule();
    modules.append(resultModule);

    logger = new LoggerService();
    logger->setSlackComponent(slackComponent);
    services.append(logger);
}

void AppController::releaseConstruct()
{
    userData = new UserData();
    standData = new StandData();
    gameSession = new GameSession();

    rfidComponent = new RFIDComponent();
    components.append(rfidComponent);

    mindWaveComponent = new MindwaveComponent();
    components.append(mindWaveComponent);

    serverComponent = new ServerComponent();
    components.append(serverComponent);

    slackComponent = new SlackComponent();
    components.append(slackComponent);

    healthCheckerComponent = new HealthCheckerComponent();
    healthCheckerComponent->addComponent(rfidComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);

    loginModule = new LoginModule();
    connect(loginModule, SIGNAL(loginStateChanged(LoginModule::LoginState)), this, SLOT(onLoginStateChanged(LoginModule::LoginState)));

    loginModule->setRFIDComponent(rfidComponent);
    loginModule->setUserData(userData);
    modules.append(loginModule);

    instructionModule = new InstructionModule();
    modules.append(instructionModule);

    gameModule = new GameModule();
    gameModule->setMindwave(mindWaveComponent);
    gameModule->setGameSession(gameSession);
    connect(gameModule, SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));
    modules.append(gameModule);

    resultModule = new ResultModule();
    modules.append(resultModule);

    logger = new LoggerService();
    logger->setSlackComponent(slackComponent);
    services.append(logger);
}

void AppController::onLoginStateChanged(LoginModule::LoginState loginState)
{
    //QString loginMsg = "login state changed  " + loginModule->getStringState();
    //logger->log(loginMsg);

    if(loginState == LoginModule::LoginState::Login)
    {
        gameModule->setUser(userData);
        gameSession->start();
    }
    else if(loginState == LoginModule::LoginState::Logout)
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

    for (auto service : services)
    {
        service->setQmlContext(qmlContext);
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

    logger->log("App state changed : " + currentModule->getName(), LogType::Verbose, LoggerService::RemoteType::Slack);
}

BaseModule* AppController::getModuleByAppState(AppState value)
{
    switch(value)
    {
    case AppState::Login: return loginModule;
    case AppState::Instruction: return instructionModule;
    case AppState::Game: return gameModule;
    case AppState::Result: return resultModule;
    }

    return nullptr;
}

void AppController::onConfigLoaded(Config* config)
{
    mindWaveComponent->setConfig(config->mindwaveData);
    rfidComponent->setConfig(config->arduinoData);
    serverComponent->setConfig(config->serverData);
    slackComponent->setConfig(config->slackData);

    standData->setConfig(config->configData);

    for (auto module : modules)
    {
        module->setConfig(config);
    }

    for (auto service : services)
    {
        service->setConfig(config);
    }

    start();
}

void AppController::onConfigError()
{
    qDebug() << "config Service Error";
}

void AppController::start()
{    
    QString initStatus = "Stand " + QString::number(standData->config().standId) + " started.........";
    logger->log(initStatus, LogType::Verbose, LoggerService::RemoteType::Slack);

    for (auto comp : components)
    {
        comp->start();
    }

    for (auto service : services)
    {
        service->start();
    }

    setAppState(AppState::Login);
}

void AppController::backtoIntro()
{
    setAppState(AppState::Login);
}


