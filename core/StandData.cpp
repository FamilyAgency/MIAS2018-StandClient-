#include "StandData.h"

StandData::StandData(QObject *parent) : QObject(parent)
{

}

void StandData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("standData", this);

}

int StandData::getStandId() const
{
   return standId;
}

