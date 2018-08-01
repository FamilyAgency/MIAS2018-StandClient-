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

void TestDriveModule::start()
{
    qDebug()<<"======================= TestDriveModule START =======================";

}

void TestDriveModule::stop()
{
    qDebug()<<"======================= TestDriveModule STOP =======================";
}

QString TestDriveModule::getName() const
{
    return "Test Drive location";
}
