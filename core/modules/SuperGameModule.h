#ifndef SUPERGAMEMODULE_H
#define SUPERGAMEMODULE_H

#include <QTimer>
#include <QObject>
#include "BaseModule.h"
#include "core/data/UserData.h"
#include "components/ServerComponent.h"

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

    void setUser(QSharedPointer<UserData> value);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void superGamePassedTest();

    void setServerComponent(QSharedPointer<ServerComponent> value);


private:
    const float superGameTimerMills = 100./60;
    int superGameTime = 1000 * 10;
    int startTime = 0;
    int superGameWinTime = 0;
    QTimer* superGameTimer = nullptr;
    QSharedPointer<UserData> currentUser;
    QSharedPointer<ServerComponent> serverComponent;

    void connectComponents();
    void disconnectComponents();

signals:
    void updateSuperGameTime(int mills);
    void superGameFailed();
    void superGameSuccess(int time);

private slots:
    void onUpdate();
    void onUserFinishedGame();

};

#endif // SUPERGAMEMODULE_H
