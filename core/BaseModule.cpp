#include "BaseModule.h"

BaseModule::BaseModule(QObject *parent) : QObject(parent)
{

}

void BaseModule::setConfig(ConfigPtr value)
{
    config = value;
}

void BaseModule::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
}



