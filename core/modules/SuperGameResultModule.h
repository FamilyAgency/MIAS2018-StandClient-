#ifndef SUPERGAMERESULTMODULE_H
#define SUPERGAMERESULTMODULE_H

#include <QObject>
#include "BaseModule.h"

class SuperGameResultModule : public BaseModule
{
    Q_OBJECT
public:
    explicit SuperGameResultModule(QObject *parent = nullptr);

    virtual ~SuperGameResultModule();
    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;

    virtual QString getName() const override;

    Q_INVOKABLE void superGameResultReadedButtonClicked();

signals:
    void superGameResultReaded();

};

#endif // SUPERGAMERESULTMODULE_H
