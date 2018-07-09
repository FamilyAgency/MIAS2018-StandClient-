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

void OneGameData::setId(int value)
{
    _id = value;
}

int OneGameData::getId() const
{
    return _id;
}

bool OneGameData::complete() const
{
    return _complete;
}

void OneGameData::setComplete(bool value)
{
    _complete = value;
}

void OneGameData::setTime(int value)
{
    _time = value;
}

int OneGameData::getTime() const
{
    return _time;
}




