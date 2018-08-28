#include "VelocityCalculator.h"
#include "tools/MathTools.h"
#include <QDebug>

VelocityCalculator::VelocityCalculator()
{

}

VelocityCalculator::VelocityCalculator(float minVelocity,
                                       float maxVelocity,
                                       float humanValueThresholdMin,
                                       float humanValueThresholdMax,
                                       float minBackVelocity,
                                       float maxBackVelocity,
                                       bool backMove)
{
    setLimits(minVelocity,
              maxVelocity,
              humanValueThresholdMin,
              humanValueThresholdMax,
              minBackVelocity,
              maxBackVelocity,
              backMove);
}

void VelocityCalculator::setLimits(float minVelocity,
                                    float maxVelocity,
                                    float humanValueThresholdMin,
                                    float humanValueThresholdMax,
                                    float minBackVelocity,
                                    float maxBackVelocity,
                                    bool backMove)
{
    this->humanValueThresholdMax = humanValueThresholdMax;
    this->humanValueThresholdMin = humanValueThresholdMin;

    this->minVelocity = minVelocity;
    this->maxVelocity = maxVelocity;

    this->minBackVelocity =  minBackVelocity;
    this->maxBackVelocity =  maxBackVelocity;
    this->backMove = backMove;
}

float VelocityCalculator::calculate(int humanValue)
{  
    float velocity = 0.0;

    humanValue = MathTools::clamp<float>(humanValue, 0, 100);

    if(humanValue >= humanValueThresholdMax)
    {

        velocity = MathTools::map<float>(humanValue, humanValueThresholdMax, 100, minVelocity,  maxVelocity);
    }
    else if (backMove)
    {
        velocity = MathTools::map<float>(humanValue, 0, humanValueThresholdMax,  minBackVelocity, maxBackVelocity);
    }

    return velocity;
}

