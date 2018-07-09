#include "IntroModule.h"

IntroModule::IntroModule(QObject *parent):BaseModule(parent)
{

}

IntroModule::~IntroModule()
{
    if(rfidComponent)
    {
        disconnect(rfidComponent.data(), SIGNAL(connectedChanged()), this, SLOT(onRFIDConnectedChanged()));
        disconnect(rfidComponent.data(), SIGNAL(onRFIDRecieve(int)), this, SLOT(onRFIDRecieve(int)));
    }

    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }
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
    if(rfidComponent)
    {
        disconnect(rfidComponent.data(), SIGNAL(connectedChanged()), this, SLOT(onRFIDConnectedChanged()));
        disconnect(rfidComponent.data(), SIGNAL(onRFIDRecieve(int)), this, SLOT(onRFIDRecieve(int)));
    }

    rfidComponent = value;
    connect(rfidComponent.data(), SIGNAL(connectedChanged()), this, SLOT(onRFIDConnectedChanged()));
    connect(rfidComponent.data(), SIGNAL(onRFIDRecieve(int)), this, SLOT(onRFIDRecieve(int)));
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

void IntroModule::onRFIDConnectedChanged()
{

}


void IntroModule::onRFIDRecieve(int id)
{
    serverComponent->fetchUser(id);
}

void IntroModule::onServerResponse(const ServerResponse& response)
{
    if(response.type == ResponseType::Error)
    {
        qDebug()<<"======================= server error =======================";
    }
    else if(response.type == ResponseType::UserFetched)
    {
        qDebug()<<"server answered  "<< response.body;
        userData->clearData();
        userData->parse(response.body);
    }
}

void IntroModule::onServerError()
{
    userData->setLoginState(UserData::LoginState::Error);
}


QString IntroModule::getName() const
{
    return "Intro location";
}
