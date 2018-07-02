#include "LoginModule.h"

LoginModule::LoginModule(QObject *parent):BaseModule(parent)
{

}

void LoginModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("loginModule", this);
}

void LoginModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
}

void LoginModule::setRFIDComponent(RFIDComponent* value)
{
    rfidComponent = value;
}

void LoginModule::setUserData(UserData* value)
{
    userData = value;
}

void LoginModule::start()
{

}

void LoginModule::stop()
{
    //userData->clearData();
}

void LoginModule::setState(LoginState value)
{
    state = value;
    emit loginStateChanged(state);
}

void LoginModule::setUserState(UserState value)
{
    userState = value;
    emit userStateChanged(value);
}

QString LoginModule::getStringState() const
{
    switch(state)
    {
        case LoginState::Login: return "user login";
        case LoginState::Logout: return "user logout";
    }
    return "undefined";
}

QString LoginModule::getName() const
{
    return "Login location";
}

