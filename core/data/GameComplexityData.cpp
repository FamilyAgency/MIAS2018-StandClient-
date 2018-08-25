#include "GameComplexityData.h"

GameComplexityData::GameComplexityData(QObject *parent) : QObject(parent)
{

}

GameComplexityData::~GameComplexityData()
{

}



void GameComplexityData::setConfig(ConfigPtr value)
{
    complexityConfig = *(value->complexityConfig);
    onNewGameComplexity(complexityConfig);
}

void GameComplexityData::start()
{
  //  connect(serverComponent.data(), SIGNAL(newGameComplexity(const ComplexityConfig&)), this, SLOT(onNewGameComplexity(const ComplexityConfig&)));

}

void GameComplexityData::onNewGameComplexity(const ComplexityConfig& value)
{
    gameComplexities = value.gameComplexities;

    const int superGameIndex = 3;
    superGameComplexity = gameComplexities[superGameIndex];

    instruction = value.instruction;
    roulette = value.roulette;
}

void GameComplexityData::update()
{

}

//void GameComplexityData::setServerComponent(QSharedPointer<ServerComponent> value)
//{
//    serverComponent = value;
//}


