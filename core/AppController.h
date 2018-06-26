#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QQmlContext>
#include <QObject>
#include <QList>
#include "components/HealthCheckerComponent.h"
#include "components/ArduinoComponent.h"
#include "components/MindwaveComponent.h"
#include "components/ServerComponent.h"
#include "StandData.h"
#include "UserData.h"
#include "tools/Logger.h"
#include "config/Config.h"
#include "LoginModule.h"
#include "InstructionModule.h"
#include "GameModule.h"
#include "ResultModule.h"
#include "Types.h"

#include "tests/LoginModuleTest.h"
#include "tests/MindwaveComponentTest.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    enum class AppState
    {
        Login,
        Instruction,
        Game,
        Result
    };
    Q_ENUMS(AppState)

    AppController(QObject *parent = nullptr);

public:   
    void setLogger(Logger* logger);    
    void setQmlContext(QQmlContext* qmlContext);

    Q_INVOKABLE void start();
    Q_INVOKABLE void startInstruction();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void startResult();

private:
    LoginModule* loginModule;
    LoginModuleTest* loginModuleTest;
    InstructionModule* instructionModule;
    GameModule* gameModule;
    ResultModule* resultModule;
    QList<BaseModule*> modules;

    HealthCheckerComponent* healthCheckerComponent;
    ArduinoComponent* arduinoComponent;
    MindwaveComponent* mindWaveComponent;
    ServerComponent* serverComponent;
    QList<BaseComponent*> components;

    StandData* standData;
    UserData* userData;
    Logger logger;
    Config* config;
    GameSession* gameSession;

    AppState appState = AppState::Login;
    BaseModule* currentModule = nullptr;

    void setAppState(AppState appState);
    BaseModule* getModuleByAppState(AppState value);

    void testConstruct();
    void releaseConstruct();

signals:
    void appStateChanged(AppState appState);


public slots:
    void onConfigLoaded(Config* config);
    void onConfigError();

private slots:
    void onLoginStateChanged(LoginModule::LoginState loginState);
    void onAllTaskComleteEvent();

};

#endif // APPCOPCONTROLLER_H
