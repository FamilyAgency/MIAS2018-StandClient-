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

    arduinoComponent = new ArduinoComponent();
    components.append(arduinoComponent);

    mindWaveComponent = new MindwaveComponentTest();
    components.append(mindWaveComponent);

    serverComponent = new ServerComponent();
    components.append(serverComponent);

    healthCheckerComponent = new HealthCheckerComponent();
    healthCheckerComponent->addComponent(arduinoComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);

    loginModule = new LoginModuleTest();
    connect(loginModule, SIGNAL(loginStateChanged(LoginModule::LoginState)), this, SLOT(onLoginStateChanged(LoginModule::LoginState)));

    loginModule->setArduino(arduinoComponent);
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
}

void AppController::releaseConstruct()
{
    userData = new UserData();
    standData = new StandData();
    gameSession = new GameSession();

    arduinoComponent = new ArduinoComponent();
    components.append(arduinoComponent);

    mindWaveComponent = new MindwaveComponent();
    components.append(mindWaveComponent);

    serverComponent = new ServerComponent();
    components.append(serverComponent);

    healthCheckerComponent = new HealthCheckerComponent();
    healthCheckerComponent->addComponent(arduinoComponent);
    healthCheckerComponent->addComponent(mindWaveComponent);
    healthCheckerComponent->addComponent(serverComponent);
    components.append(healthCheckerComponent);

    loginModule = new LoginModule();
    connect(loginModule, SIGNAL(loginStateChanged(LoginModule::LoginState)), this, SLOT(onLoginStateChanged(LoginModule::LoginState)));

    loginModule->setArduino(arduinoComponent);
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
}

void AppController::onLoginStateChanged(LoginModule::LoginState loginState)
{
    qDebug()<<"login state changed  "<< (int)loginState;
    if(loginState == LoginModule::LoginState::Login)
    {
        gameSession->start();
    }
    else if(loginState == LoginModule::LoginState::Logout)
    {
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
    arduinoComponent->setConfig(config->arduinoData);
    serverComponent->setConfig(config->serverData);

    standData->setConfig(config->configData);

    for (auto module : modules)
    {
        module->setConfig(config);
    }

    start();
}

void AppController::onConfigError()
{
    qDebug() << "config Service Error";
}

void AppController::setLogger(Logger* logger)
{
    for (auto module : modules)
    {
        module->setLogger(logger);
    }
}

void AppController::start()
{
    setAppState(AppState::Login);
}
