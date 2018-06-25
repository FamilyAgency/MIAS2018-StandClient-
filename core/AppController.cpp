#include "AppController.h"

AppController::AppController(QObject *parent) : QObject(parent)
{
    userData = new UserData();
    standData = new StandData();
    gameSession = new GameSession();

    arduinoComponent = new ArduinoComponent();
    mindWaveComponent = new MindwaveComponent();
    healthCheckerComponent = new HealthCheckerComponent(arduinoComponent, mindWaveComponent);

    // loginModule = new LoginModule(arduinoComponent);
    // loginModule->setArduino(arduinoComponent);
    // modules.append(loginModule);

    loginModule = new LoginModuleTest();
    connect(loginModule, SIGNAL(loginStateChanged(LoginModule::LoginState)), this, SLOT(onLoginStateChanged(LoginModule::LoginState)));

    loginModule->setArduino(arduinoComponent);
    loginModule->setUserData(userData);
    modules.append(loginModule);

    instructionModule = new InstructionModule();
    modules.append(instructionModule);

    gameModule = new GameModule();
    connect(gameModule, SIGNAL(allTaskComleteEvent()), this, SLOT(onAllTaskComleteEvent()));

    gameModule->setGameSession(gameSession);
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
        currentModule->stop();
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
    for (auto module : modules)
    {
        module->setQmlContext(qmlContext);
    }

    userData->setQmlContext(qmlContext);
    standData->setQmlContext(qmlContext);
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
