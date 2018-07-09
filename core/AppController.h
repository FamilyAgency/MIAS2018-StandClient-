#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QQmlContext>
#include <QObject>
#include <QList>

#include "components/HealthCheckerComponent.h"
#include "components/RFIDComponent.h"
#include "components/MindwaveComponent.h"
#include "components/ServerComponent.h"
#include "components/SlackComponent.h"
#include "components/LoggerComponent.h"

#include "data/StandData.h"
#include "data/UserData.h"
#include "config/Config.h"

#include "modules/IntroModule.h"
#include "modules/InstructionModule.h"
#include "modules/GameModule.h"
#include "modules/ResultModule.h"
#include "Types.h"

#include "tests/IntroModuleTest.h"
#include "tests/MindwaveComponentTest.h"
#include "tests/ServerComponentTest.h"

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

    explicit AppController(QObject *parent = nullptr);
    virtual ~AppController();

    void setQmlContext(QQmlContext* qmlContext);

    Q_INVOKABLE void start();
    Q_INVOKABLE void startInstruction();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void startResult();
    Q_INVOKABLE void backtoIntro();

private:
    QSharedPointer<IntroModule> introModule;
    QSharedPointer<IntroModuleTest> introModuleTest;
    QSharedPointer<InstructionModule> instructionModule;
    QSharedPointer<GameModule> gameModule;
    QSharedPointer<ResultModule> resultModule;
    QList<QSharedPointer<BaseModule>> modules;

    QSharedPointer<LoggerComponent> logger;
    QSharedPointer<HealthCheckerComponent> healthCheckerComponent;
    QSharedPointer<RFIDComponent> rfidComponent;
    QSharedPointer<MindwaveComponent> mindWaveComponent;
    QSharedPointer<ServerComponent> serverComponent;
    QList<QSharedPointer<BaseComponent>> components;

    QSharedPointer<StandData> standData;
    QSharedPointer<UserData> userData;
    ConfigPtr config;
    QSharedPointer<GameSession> gameSession;

    AppState appState = AppState::Login;
    QSharedPointer<BaseModule> currentModule = nullptr;

    void setAppState(AppState appState);
    QSharedPointer<BaseModule> getModuleByAppState(AppState value);

    void testConstruct();
    void releaseConstruct();

signals:
    void appStateChanged(AppState appState);

public slots:
    void onConfigLoaded(ConfigPtr config);
    void onConfigError();

private slots:
    void onLoginStateChanged(UserData::LoginState loginState);
    void onAllTaskComleteEvent();

};

#endif // APPCOPCONTROLLER_H
