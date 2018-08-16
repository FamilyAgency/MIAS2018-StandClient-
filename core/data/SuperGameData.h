#ifndef SUPERGAMEDATA_H
#define SUPERGAMEDATA_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QString>
#include "core/game/VelocityCalculator.h"
#include "config/Config.h"

class SuperGameData
{
public:
    explicit SuperGameData();

    void setPath(const QVector<QPointF>& path);
    void setDifficult(const VelocityCalculator& value);
    void clearUserData();

    QVector<QPointF> getPath() const;
    VelocityCalculator getDifficult() const;

    void setId(int value);
    int getId() const;

    bool complete() const;
    void setComplete(bool value);
    void setTime(int value);
    int getTime() const;

    void setMaxTime(int value);
    int getMaxTime() const;

private:
    QVector<QPointF> path;
    VelocityCalculator difficult;
    int featureId = 1;
    int _id = 1;
    int _time = 0;
    int _maxTime;
    bool _complete = false;
};

#endif // SUPERGAMEDATA_H
