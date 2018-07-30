#ifndef APPCOPCONTROLLER_H
#define APPCOPCONTROLLER_H

#include <QQmlContext>
#include <QObject>
#include <QList>

#include "components/HealthCheckerComponent.h"
#include "components/mindwave/MindwaveComponentBase.h"
#include "components/ServerComponent.h"
#include "components/SlackComponent.h"
#include "components/LoggerComponent.h"
#include "components/MonitoringComponent.h"

#include "data/StandData.h"
#include "data/UserData.h"
#include "config/Config.h"

#include "modules/IntroModule.h"
#include "modules/InstructionModule.h"
#include "modules/RouletteModule.h"
#include "modules/GameModule.h"
#include "modules/GameResultModule.h"
#include "modules/SuperGameModule.h"
#include "modules/SuperGameResultModule.h"

#include "Types.h"

#include "tests/MindwaveComponentTest.h"
#include "tests/RFIDComponentTest.h"

#include "tools/AppSettings.h"

class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject *parent = nullptr);
    virtual ~AppController();

    enum class AppState
    {
        Intro,
        Instruction,
        Roulette,
        Game,
        GameResult,
        SuperGame,
        SuperGameResult
    };
    Q_ENUMS(AppState)

    void setQmlContext(QQmlContext* qmlContext);

    Q_INVOKABLE void start();
    Q_INVOKABLE void startInstruction();
    Q_INVOKABLE void startRoulette();
    Q_INVOKABLE void startGame();
    Q_INVOKABLE void startGameResult();
    Q_INVOKABLE void startSuperGame();
    Q_INVOKABLE void backToIntro();

    Q_INVOKABLE void testCrash();
    Q_INVOKABLE AppState getAppState() const;

private:
    QSharedPointer<IntroModule> introModule;
    QSharedPointer<InstructionModule> instructionModule;
    QSharedPointer<GameModule> gameModule;
    QSharedPointer<GameResultModule> gameResultModule;
    QSharedPointer<RouletteModule> rouletteModule;
    QSharedPointer<SuperGameModule> superGameModule;
    QSharedPointer<SuperGameResultModule> superGameResultModule;
    QList<QSharedPointer<BaseModule>> modules;

    QSharedPointer<LoggerComponent> loggerComponent;
    QSharedPointer<HealthCheckerComponent> healthCheckerComponent;
    QSharedPointer<RFIDComponent> rfidComponent;
    QSharedPointer<MindwaveComponentBase> mindWaveComponent;
    QSharedPointer<ServerComponent> serverComponent;
    QSharedPointer<MonitoringComponent> monitoringComponent;
    QList<QSharedPointer<BaseComponent>> components;

    QSharedPointer<StandData> standData;
    QSharedPointer<UserData> userData;
    ConfigPtr config;
    QSharedPointer<GameSession> gameSession;
    AppSettings appSettings;

    AppState appState = AppState::Intro;
    QSharedPointer<BaseModule> currentModule = nullptr;

    void setAppState(AppState appState);
    QSharedPointer<BaseModule> getModuleByAppState(AppState value);

    void createEngine();

    template <class MindwaveComponentT>
    void createMindwave();

    template <class RFIDComponentT>
    void createRFID();

signals:
    void appStateChanged(AppState appState);
    void configError(const QString& errorMessage);

public slots:
    void onConfigLoaded(ConfigPtr config);
    void onConfigError(const QString& errorMessage);

private slots:
    void onAllTaskComleteEvent();
    void onServerResponse(const ServerResponse& response);
    void onCarStarting();
    void onGameCategoryUpdate(int id);
    void onSuperGameFailed();
    void onSuperGameSuccess(int time);
    void onUserStartPlay();
};

#endif // APPCOPCONTROLLER_H
