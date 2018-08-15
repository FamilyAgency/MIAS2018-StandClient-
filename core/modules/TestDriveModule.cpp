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
    connect(serverComponent.data(), SIGNAL(dealersDataUpdated(const QVariantList&)), this, SLOT(onDealersDataUpdated(const QVariantList&)));
    connect(serverComponent.data(), SIGNAL(testDriveRequestSuccess()), this, SLOT(onTestDriveRequestSuccess()));

    if(!(dealersLoaded && loadOnlyOnce))
    {
        serverComponent->getDealersRequest();
    }

}

void TestDriveModule::stop()
{
    qDebug()<<"======================= TestDriveModule STOP =======================";
    disconnect(serverComponent.data(), SIGNAL(dealersDataUpdated(const QVariantList&)), this, SLOT(onDealersDataUpdated(const QVariantList&)));
    disconnect(serverComponent.data(), SIGNAL(testDriveRequestSuccess()), this, SLOT(onTestDriveRequestSuccess()));
}

void TestDriveModule::onDealersDataUpdated(const QVariantList& data)
{
    qDebug()<<"dilers data income";

    dealersLoaded = data.length() > 0;
    emit dealersDataUpdated(data);
}

void TestDriveModule::onTestDriveRequestSuccess()
{
    emit testDriveRequestSuccess();
}

void TestDriveModule::makeTestDrive(int dealerId)
{
    serverComponent->testDriveRequest(1500/*currentUser->baseUserData().id*/, dealerId);
}

QString TestDriveModule::getName() const
{
    return "Test Drive location";
}
