#include "IntroModule.h"

IntroModule::IntroModule(QObject *parent):BaseModule(parent)
{

}

IntroModule::~IntroModule()
{
    disconnectComponents();
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
    serverComponent = qobject_cast<QSharedPointer<ServerRemoteComponent>>(value);
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
    rfidComponent->startReadingId();
    connectComponents();
}

void IntroModule::stop()
{
    qDebug()<<"======================= IntroModule STOP =======================";
    disconnectComponents();
}

void IntroModule::onUserReadSuccess(const QString& data)
{
    qDebug()<<"id readed "<<data;

   // serverComponent->clearBaseUserData();
    serverComponent->searchUserByIdRequest(data.toInt());
}

void IntroModule::onNewUserEntered(const UserObject& userObject)
{
    qDebug()<<"onNewUserEntered";
    userData->clearData();
    userData->setNewUserData(userObject);

    if(userData->canPlay())
    {
        qDebug()<<"canPlay";
        emit userStartPlay();
    }
}

void IntroModule::onUserNotFound()
{
    emit userNotFound();
}

void IntroModule::onServerError()
{
    //userData->setLoginState(UserData::LoginState::Error);
}

QString IntroModule::getName() const
{
    return "Intro location";
}

void IntroModule::connectComponents()
{
    if(serverComponent)
    {
        connect(serverComponent.data(), SIGNAL(newUserEntered(const UserObject&)), this, SLOT(onNewUserEntered(const UserObject&)));
        connect(serverComponent.data(), SIGNAL(userNotFound()), this, SLOT(onUserNotFound()));
    }

    if(rfidComponent)
    {
       connect(rfidComponent.data(), SIGNAL(userReadSuccess(const QString&)), this, SLOT(onUserReadSuccess(const QString&)));
    }
}

void IntroModule::disconnectComponents()
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(newUserEntered(const UserObject&)), this, SLOT(onNewUserEntered(const UserObject&)));
        disconnect(serverComponent.data(), SIGNAL(userNotFound()), this, SLOT(onUserNotFound()));
    }

    if(rfidComponent)
    {
        disconnect(rfidComponent.data(), SIGNAL(userReadSuccess(const QString& )), this, SLOT(onUserReadSuccess(const QString&)));
    }
}
