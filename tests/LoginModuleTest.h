#ifndef LOGINMODULETEST_H
#define LOGINMODULETEST_H

#include <QObject>
#include "core/LoginModule.h"
#include "tests/LoginModuleTest.h"

class LoginModuleTest : public LoginModule
{
    Q_OBJECT
public:
    LoginModuleTest();
    virtual void setQmlContext(QQmlContext* qmlContext) override;

    Q_INVOKABLE virtual void loginSuccessTest();
    Q_INVOKABLE virtual void logoutTest();
signals:

public slots:
};

#endif // LOGINMODULETEST_H
