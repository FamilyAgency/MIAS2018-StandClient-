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
    // connect on new id
}

void LoginModule::setServerComponent(ServerComponent* value)
{
    if(serverComponent)
    {
        disconnect(serverComponent, SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }
    serverComponent = value;
    connect(serverComponent, SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
}

void LoginModule::setUserData(UserData* value)
{
    userData = value;
}

void LoginModule::setStandData(StandData* value)
{
    standData = value;
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
        case LoginState::Login: return "User login";
        case LoginState::Logout: return "User logout";
    }
    return "undefined";
}

QString LoginModule::getName() const
{
    return "Login location";
}

void LoginModule::onRFIDRecieve(int id)
{
    serverComponent->fetchUser(standData->config().standId, id);
}

void LoginModule::onServerResponse(const ServerResponse& response)
{
    if(response.type == ResponseType::UserFetched)
    {
        parseServerResponse(response.body);
    }
}

void LoginModule::onServerError()
{
    setState(LoginState::Error);
}

void LoginModule::parseServerResponse(const QString& data)
{
      qDebug()<<"server answered  "<< data;
      //setUserState(UserState::DoesntExists);
}
