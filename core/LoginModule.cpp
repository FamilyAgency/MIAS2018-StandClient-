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
