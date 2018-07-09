#include "IntroModule.h"

IntroModule::IntroModule(QObject *parent):BaseModule(parent)
{

}

IntroModule::~IntroModule()
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

void IntroModule::setRFIDComponent(QSharedPointer<RFIDComponent> value)
{
    rfidComponent = value;
    // connect on new id
}

void IntroModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }
    serverComponent = value;
    connect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
}

void IntroModule::setUserData(QSharedPointer<UserData> value)
{
    userData = value;
}

void IntroModule::setStandData(QSharedPointer<StandData> value)
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
    userData->setLoginState(UserData::LoginState::Error);
}

void IntroModule::parseServerResponse(const QString& data)
{
      qDebug()<<"server answered  "<< data;
      //setUserState(UserState::DoesntExists);
}
