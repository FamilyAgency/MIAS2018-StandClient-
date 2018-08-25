#ifndef VELOCITYCALCULATOR_H
#define VELOCITYCALCULATOR_H

#include <QObject>

class VelocityCalculator
{
public:
    VelocityCalculator();
    VelocityCalculator(float minVelocity,
                       float maxVelocity,
                       float humanValueThresholdMin,
                       float humanValueThresholdMax = 100.0f,
                       float minBackVelocity = -1.0f,
                       float maxBackVelocity = -.5f,
                       bool backMove = true);

    float calculate(int humanValue);

    void setLimits(float minVelocity,
                    float maxVelocity,
                    float humanValueThresholdMin,
                    float humanValueThresholdMax = 100.0f,
                    float minBackVelocity = -1.0f,
                    float maxBackVelocity = -.5f,
                    bool backMove = true);

    float getThreshold() const
    {
       return humanValueThresholdMin / humanValueThresholdMax;
    }

public:
    float humanValueThresholdMax = 100;
    float humanValueThresholdMin = 60;

    float minVelocity = 0;
    float maxVelocity = 3;

    float minBackVelocity =  -2;
    float maxBackVelocity =  -1;

    bool backMove = true;
};

#endif // VELOCITYCALCULATOR_H
