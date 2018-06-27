#ifndef LOGINMODULETEST_H
#define LOGINMODULETEST_H

#include <QObject>
#include "core/LoginModule.h"
#include "tests/LoginModuleTest.h"
#include "core/game/VelocityCalculator.h"

class LoginModuleTest : public LoginModule
{
    Q_OBJECT
public:
    LoginModuleTest();
    virtual void setQmlContext(QQmlContext* qmlContext) override;

    Q_INVOKABLE virtual void loginSuccessTest();
    Q_INVOKABLE virtual void logoutTest();

private:
    QVector<QPointF> createPath(int pathId);
    VelocityCalculator createDifficult(int diff);

signals:

public slots:
};

#endif // LOGINMODULETEST_H
