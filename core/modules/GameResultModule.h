#ifndef GAMERESULTMODULE_H
#define GAMERESULTMODULE_H

#include <QObject>
#include "BaseModule.h"

class GameResultModule : public BaseModule
{
    Q_OBJECT
public:
    explicit GameResultModule(QObject *parent = nullptr);

    virtual ~GameResultModule();
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;
    virtual void setQmlContext(QQmlContext* value) override;

    Q_INVOKABLE void superGameAcceptedButtonClick();
    Q_INVOKABLE void superGameRejectedButtonClick();

signals:
    void superGameAccepted();
    void superGameRejected();
};

#endif // GAMERESULTMODULE_H
