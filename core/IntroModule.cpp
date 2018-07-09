#include "IntroModule.h"

IntroModule::IntroModule(QObject *parent):BaseModule(parent)
{

}

void IntroModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("introModule", this);
}

void IntroModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void IntroModule::setRFIDComponent(RFIDComponent* value)
{
    rfidComponent = value;
    // connect on new id
}

void IntroModule::setServerComponent(ServerComponent* value)
{
    if(serverComponent)
    {
        disconnect(serverComponent, SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }
    serverComponent = value;
    connect(serverComponent, SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
}

void IntroModule::setUserData(UserData* value)
{
    userData = value;
}

void IntroModule::setStandData(StandData* value)
{
    standData = value;
}

void IntroModule::start()
{

}

void IntroModule::stop()
{
    //userData->clearData();
}

void IntroModule::setState(LoginState value)
{
    state = value;
    emit loginStateChanged(state);
}

void IntroModule::setUserState(UserState value)
{
    userState = value;
    emit userStateChanged(value);
}

QString IntroModule::getStringState() const
{
    switch(state)
    {
        case LoginState::Login: return "User login";
        case LoginState::Logout: return "User logout";
    }
    return "undefined";
}

QString IntroModule::getName() const
{
    return "Login location";
}

void IntroModule::onRFIDRecieve(int id)
{
   // serverComponent->fetchUser(standData->config().app, id);
}

void IntroModule::onServerResponse(const ServerResponse& response)
{
    if(response.type == ResponseType::UserFetched)
    {
        parseServerResponse(response.body);
    }
}

void IntroModule::onServerError()
{
    setState(LoginState::Error);
}

void IntroModule::parseServerResponse(const QString& data)
{
      qDebug()<<"server answered  "<< data;
      //setUserState(UserState::DoesntExists);
}
