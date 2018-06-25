#include "LoginModuleTest.h"

LoginModuleTest::LoginModuleTest():LoginModule()
{

}

void LoginModuleTest::setQmlContext(QQmlContext* qmlContext)
{
     qmlContext->setContextProperty("loginModule", this);
}

void LoginModuleTest::loginSuccessTest()
{
    userData->setName("Александр");
    userData->setSurname("Александров");
    userData->setId(665);
    emit loginStateChanged(LoginState::Login);
}

void LoginModuleTest::logoutTest()
{
    userData->setName("");
    userData->setSurname("");
    userData->setId(-1);
    emit loginStateChanged(LoginState::Logout);
}


