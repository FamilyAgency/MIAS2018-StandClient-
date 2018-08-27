#ifndef SUPERGAMEMODULE_H
#define SUPERGAMEMODULE_H

#include <QTimer>
#include <QObject>
#include "BaseModule.h"
#include "core/data/UserData.h"
#include "components/ServerComponent.h"
#include "core/game/GameCountDown.h"
#include "core/game/GameTask.h"

class SuperGameModule : public BaseModule
{
    Q_OBJECT
public:
    explicit SuperGameModule(QObject *parent = nullptr);
    virtual ~SuperGameModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    void setMindWaveClient(QSharedPointer<MindwaveComponentBase> value);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE float getPercent() const;
    Q_INVOKABLE float getSuperGameTime() const;
    Q_INVOKABLE QVariantList getGameUncompletedPath() const;
    Q_INVOKABLE float getMindwaveLimit() const;


    Q_INVOKABLE QVariantList getCompletedPath() const;

    Q_INVOKABLE bool isRunning() const;
    Q_INVOKABLE bool isPreTaskState() const;

    Q_INVOKABLE QPointF getStartPoint() const;
    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE float getForwardVectorRotation() const;
    Q_INVOKABLE QVector2D getForwardVector() const;

    void setUser(QSharedPointer<UserData> value);
    void setServerComponent(QSharedPointer<ServerComponent> value);


    Q_INVOKABLE void superGamePassedTest();
    Q_INVOKABLE void superGameFailedTest();

private:
    const float superGameTimerMills = 100.0f/60.0f;
    int superGameTime = 1000 * 10;
    int startTime = 0;
    int superGameWinTime = 0;
    float percent = 0.0f;
    bool _taskRunning;
    void setTaskRunning(bool value);

    QTimer* superGameTimer = nullptr;
    QSharedPointer<UserData> currentUser;
    QSharedPointer<ServerComponent> serverComponent;
    QSharedPointer<GameCountDown> gameCountDown = nullptr;

    QSharedPointer<GameTask> gameTask = nullptr;
    QVariantList gameCompletedPath, gameUncompletedPath;
    void connectComponents();
    void disconnectComponents();

signals:
    void updateSuperGameTime(int mills);
    void superGameFailed();
    void superGameSuccess(int time);
    void superGameStarted();
    void countDownUpdate(float time);
    void countDownComplete();

    void updateCanvas();
    void taskComleteEvent(float time);


private slots:
    void onUpdate();
    void onUserFinishedGame();

    void onCountDownUpdate(float countDown);
    void onCountDownComplete();

    void onTaskUpdateEvent();
    void onTaskCompleteEvent();

    void onNewCompletedPoint(const QPointF& point);

};

#endif // SUPERGAMEMODULE_H
