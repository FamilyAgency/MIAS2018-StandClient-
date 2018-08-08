#include "TestDriveModule.h"

TestDriveModule::TestDriveModule(QObject *parent) : BaseModule(parent)
{

}

TestDriveModule::~TestDriveModule()
{

}

void TestDriveModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("testDriveModule", this);
}

void TestDriveModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void TestDriveModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
}

void TestDriveModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}

void TestDriveModule::setDilerData(QSharedPointer<DilerData> value)
{
    dilerData = value;
}

void TestDriveModule::start()
{
    qDebug()<<"======================= TestDriveModule START =======================";
    connect(serverComponent.data(), SIGNAL(dilersDataUpdated(const QVariantList&)), this, SLOT(onDilersDataUpdated(const QVariantList&)));
    serverComponent->getDealersRequest();
}

void TestDriveModule::stop()
{
    qDebug()<<"======================= TestDriveModule STOP =======================";
    disconnect(serverComponent.data(), SIGNAL(dilersDataUpdated(const QVariantList&)), this, SLOT(onDilersDataUpdated(const QVariantList&)));
}

void TestDriveModule::onDilersDataUpdated(const QVariantList& data)
{
    qDebug()<<"dilers data income";
    emit dilersDataUpdated(data);
}

void TestDriveModule::makeTestDrive(int dealerId)
{
    serverComponent->testDriveRequest(currentUser->baseUserData().id, dealerId);
}

QString TestDriveModule::getName() const
{
    return "Test Drive location";
}
