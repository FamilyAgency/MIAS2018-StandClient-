#include "OneGameData.h"

OneGameData::OneGameData()
{

}

void OneGameData::setDescription(const QString& value)
{
    description = value;
}

void OneGameData::setPath(const QVector<QPointF>& value)
{
    path = value;
}

void OneGameData::setDifficult(const VelocityCalculator& value)
{
    difficult = value;
}

QVector<QPointF> OneGameData::getPath() const
{
    return path;
}

VelocityCalculator OneGameData::getDifficult() const
{
    return difficult;
}

void OneGameData::clearUserData()
{

}



