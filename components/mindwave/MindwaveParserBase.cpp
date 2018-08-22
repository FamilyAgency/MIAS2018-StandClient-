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

