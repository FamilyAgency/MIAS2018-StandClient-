#include "AdvantagesData.h"

AdvantagesData::AdvantagesData(QObject *parent) : QObject(parent)
{

}

void AdvantagesData::setConfig(ConfigPtr value)
{
    advantagesConfig = *value->advantagesConfig;
    advantages = advantagesConfig.advantages;
    advantageIndex = 0;
}

OneAdvantageConfig AdvantagesData::getNextAdvantage()
{
    if(++advantageIndex >= advantagesConfig.advantages.length())
    {
        std::random_shuffle(advantages.begin(), advantages.end());
        advantageIndex = 0;
    }

    return advantages[advantageIndex];
}

void AdvantagesData::shuffle()
{

}
