#include "VelocityCalculator.h"
#include "tools/MathTools.h"

VelocityCalculator::VelocityCalculator()
{

}

VelocityCalculator::VelocityCalculator(float minVelocity,
                                       float maxVelocity,
                                       float humanValueThresholdMin,
                                       float humanValueThresholdMax,
                                       float minBackVelocity,
                                       float maxBackVelocity)
{
    setLimits(minVelocity, maxVelocity, humanValueThresholdMin, humanValueThresholdMax, minBackVelocity, maxBackVelocity);
}

void VelocityCalculator::setLimits(float minVelocity,
                                    float maxVelocity,
                                    float humanValueThresholdMin,
                                    float humanValueThresholdMax,
                                    float minBackVelocity,
                                    float maxBackVelocity)
{
    this->humanValueThresholdMax = humanValueThresholdMax;
    this->humanValueThresholdMin = humanValueThresholdMin;

    this->minVelocity = minVelocity;
    this->maxVelocity = maxVelocity;

    this->minBackVelocity =  minBackVelocity;
    this->maxBackVelocity =  maxBackVelocity;
}

float VelocityCalculator::calculate(int humanValue)
{
    int min = 50;
    int max = 100;

    humanValue = 100;// qrand() % ((max + 1) - min) + min;

    float velocity = 0.0;

    if(humanValue > humanValueThresholdMin)
    {
        velocity = MathTools::map<float>(humanValue, humanValueThresholdMin,  humanValueThresholdMax, minVelocity,  maxVelocity);
    }
    else if (backMove)
    {
        velocity = MathTools::map<float>(humanValue, 0, humanValueThresholdMin,  minBackVelocity, maxBackVelocity);
    }

    return velocity;
}

