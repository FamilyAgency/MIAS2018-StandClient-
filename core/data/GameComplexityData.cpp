#include "GameComplexityData.h"
#include "components/ServerComponent.h"

GameComplexityData::GameComplexityData(QObject *parent) : QObject(parent)
{

}

GameComplexityData::~GameComplexityData()
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(newGameComplexity(const ComplexityConfig&)), this, SLOT(onNewGameComplexity(const ComplexityConfig&)));
    }
}

void GameComplexityData::setConfig(ConfigPtr value)
{
    complexityConfig = *(value->complexityConfig);
    onNewGameComplexity(complexityConfig);
}

void GameComplexityData::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
}

void GameComplexityData::start()
{
    connect(serverComponent.data(), SIGNAL(newGameComplexity(const ComplexityConfig&)), this, SLOT(onNewGameComplexity(const ComplexityConfig&)));
}

void GameComplexityData::checkComplexity()
{
    serverComponent->checkComplexity();
}

void GameComplexityData::onNewGameComplexity(const ComplexityConfig& value)
{
    qDebug()<<"log complexity config  "<<value.instruction;


    gameComplexities = value.gameComplexities;

    const int superGameIndex = 3;
    superGameComplexity = gameComplexities[superGameIndex];

    instruction = value.instruction;
    roulette = value.roulette;
}

