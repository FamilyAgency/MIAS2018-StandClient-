#include "SuperGameResultModule.h"

SuperGameResultModule::SuperGameResultModule(QObject *parent) : BaseModule(parent)
{

}

SuperGameResultModule::~SuperGameResultModule()
{

}

void SuperGameResultModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("superGameResultModule", this);
}

void SuperGameResultModule::start()
{
    qDebug()<<"======================= SuperGame Result Module START =======================";

}

void SuperGameResultModule::stop()
{
    qDebug()<<"======================= SuperGame Result Module STOP =======================";
}

void SuperGameResultModule::superGameResultReadedButtonClicked()
{
    emit superGameResultReaded();
}

QString SuperGameResultModule::getName() const
{
    return "Super Game Result location";
}

