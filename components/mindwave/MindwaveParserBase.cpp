#include "MindwaveParserBase.h"
#include "tools/MathTools.h"

MindwaveParserBase::MindwaveParserBase(QObject *parent) : QObject(parent)
{

}

void MindwaveParserBase::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
}

void MindwaveParserBase::onDataRecieve(const QString& data)
{
    parse(data);
}

void MindwaveParserBase::onDataRecieve(const QByteArray& data)
{
    parse(data);
}

void MindwaveParserBase::parse(const QString& data)
{

}

void MindwaveParserBase::parse(const QByteArray& data)
{

}

QString MindwaveParserBase::getPoorSignalColor(int value) const
{
    QString color = "#999999";

    if(value >= 66 && value <= 100)
    {
        color = "#009900";
    }
    else if(value >= 30 && value <= 66)
    {
        color = "#999900";
    }
    else if(value >= 0 && value <= 30)
    {
        color = "#999999";
    }

    return color;
}

int MindwaveParserBase::remapPoorSignalLevel(int signalValue) const
{
    return MathTools::map<float>(signalValue, 0,  200, 100,  0);
}

