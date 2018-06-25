#include "BaseModule.h"

BaseModule::BaseModule(QObject *parent) : QObject(parent)
{

}

void BaseModule::setConfig(Config* value)
{
    config = value;
}

void BaseModule:: setLogger(Logger* value)
{
    logger = value;
}

void BaseModule::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
}



