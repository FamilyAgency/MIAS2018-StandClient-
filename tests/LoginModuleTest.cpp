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

    userData->setFirstTime(true);
    userData->setFirstTime(true);
    userData->setFinished(false);
    userData->setExists(true);
    userData->setWaitEnoughToPlay(true);

    GameProgress* gameProgress = new GameProgress();
    userData->setGameProgess(gameProgress);
    setState(LoginState::Login);
}

void LoginModuleTest::logoutTest()
{
    userData->setName("");
    userData->setSurname("");
    userData->setId(-1);
    setState(LoginState::Logout);
}


