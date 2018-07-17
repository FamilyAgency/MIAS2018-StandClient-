#ifndef SUPERGAMEMODULE_H
#define SUPERGAMEMODULE_H

#include <QTimer>
#include <QObject>
#include "BaseModule.h"

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

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void superGamePassedTest();

private:
    const float superGameTimerMills = 100./60;
    const int superGameTime = 1000 * 10;
    int startTime = 0;
    QTimer* superGameTimer = nullptr;

signals:
    void updateSuperGameTime(int mills);
    void superGameFailed();
    void superGameSuccess(int time);

public slots:
    void onUpdate();
};

#endif // SUPERGAMEMODULE_H
