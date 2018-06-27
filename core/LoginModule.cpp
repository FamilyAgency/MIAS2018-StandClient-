#include "LoginModule.h"

LoginModule::LoginModule(QObject *parent):BaseModule(parent)
{

}

void LoginModule::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("loginModule", this);
}

void LoginModule::setConfig(Config* config)
{
    BaseModule::setConfig(config);
}

void LoginModule::setArduino(ArduinoComponent* arduinoComponentValue)
{
    arduinoComponent = arduinoComponentValue;
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

}

void LoginModule::setState(LoginState value)
{
    state = value;
    emit loginStateChanged(state);
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

