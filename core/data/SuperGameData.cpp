#include "SuperGameData.h"

SuperGameData::SuperGameData()
{

}

void SuperGameData::setPath(const QVector<QPointF>& value)
{
    path = value;
}


void SuperGameData::setComplexity(const OneGameComplexityConfig& value)
{
    difficult.setLimits(value.velocityMin,
                        value.velocityMax,
                        value.attentionMin,
                        value.attentionMax,
                        value.velocityBackMin,
                        value.velocityBackMax,
                        value.backMove);
}

QVector<QPointF> SuperGameData::getPath() const
{
    return path;
}

VelocityCalculator SuperGameData::getDifficult() const
{
    return difficult;
}

void SuperGameData::clearUserData()
{

}

void SuperGameData::setId(int value)
{
    _id = value;
}

int SuperGameData::getId() const
{
    return _id;
}

bool SuperGameData::complete() const
{
    return _complete;
}

void SuperGameData::setComplete(bool value)
{
    _complete = value;
}

void SuperGameData::setTime(int value)
{
    _time = value;
}

int SuperGameData::getTime() const
{
    return _time;
}

void SuperGameData::setMaxTime(int value)
{
     _maxTime = value;
}

int SuperGameData::getMaxTime() const
{
    return _maxTime;
}
