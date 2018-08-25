#include "OneStageData.h"

OneStageData::OneStageData()
{

}

void OneStageData::setPath(const QVector<QPointF>& value)
{
    path = value;
}

void OneStageData::setComplexity(const OneGameComplexityConfig& value)
{
    difficult.setLimits(value.velocityMin,
                        value.velocityMax,
                        value.attentionMin,
                        value.attentionMax,
                        value.velocityBackMin,
                        value.velocityBackMax,
                        value.backMove);
}

QVector<QPointF> OneStageData::getPath() const
{
    return path;
}

VelocityCalculator OneStageData::getDifficult() const
{
    return difficult;
}

void OneStageData::clearUserData()
{

}

void OneStageData::setId(int value)
{
    _id = value;
}

int OneStageData::getId() const
{
    return _id;
}

bool OneStageData::complete() const
{
    return _complete;
}

void OneStageData::setComplete(bool value)
{
    _complete = value;
}

void OneStageData::setTime(int value)
{
    _time = value;
}

int OneStageData::getTime() const
{
    return _time;
}





