#include "MindwaveParserBase.h"


MindwaveParserBase::MindwaveParserBase(QObject *parent) : QObject(parent)
{

}

void MindwaveParserBase::setConfig(const MindwaveConfig& config)
{
    mindwaveConfig = config;
}

MindwaveData MindwaveParserBase::parse(const QString& data)
{
    MindwaveData mindwaveData;  
    return mindwaveData;
}

MindwaveData MindwaveParserBase::parseOneDataChunck(const QString& data)
{
   MindwaveData mindwaveData;
   return mindwaveData;
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
