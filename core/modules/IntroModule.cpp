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
    rfidComponent = value;
}

void IntroModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
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
    qDebug()<<"======================= IntroModule START =======================";

    if(serverComponent)
    {
        connect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }

    if(rfidComponent)
    {
        connect(rfidComponent.data(), SIGNAL(connectedChanged()), this, SLOT(onRFIDConnectedChanged()));
        connect(rfidComponent.data(), SIGNAL(onRFIDRecieve(int)), this, SLOT(onRFIDRecieve(int)));
    }
}

void IntroModule::stop()
{
    qDebug()<<"======================= IntroModule STOP =======================";

    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(serverResponse(const ServerResponse&)), this, SLOT(onServerResponse(const ServerResponse&)));
    }

    if(rfidComponent)
    {
        disconnect(rfidComponent.data(), SIGNAL(connectedChanged()), this, SLOT(onRFIDConnectedChanged()));
        disconnect(rfidComponent.data(), SIGNAL(onRFIDRecieve(int)), this, SLOT(onRFIDRecieve(int)));
    }
}

void IntroModule::onRFIDConnectedChanged()
{

}


void IntroModule::onRFIDRecieve(int id)
{
    if(canFetchUser())
    {
        serverComponent->fetchUser(id);
    }
}

bool IntroModule::canFetchUser() const
{
    //server busy, main screen
    return true;
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
