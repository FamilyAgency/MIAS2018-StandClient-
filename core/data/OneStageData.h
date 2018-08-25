#ifndef ONEGAMEDATA_H
#define ONEGAMEDATA_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QString>
#include "core/game/VelocityCalculator.h"
#include "config/Config.h"

class OneStageData
{
public:
    explicit OneStageData();

    void setPath(const QVector<QPointF>& path);
 //   void setDifficult(const VelocityCalculator& value);
    void setComplexity(const OneGameComplexityConfig& value);

    void clearUserData();

    QVector<QPointF> getPath() const;
    VelocityCalculator getDifficult() const;

    void setId(int value);
    int getId() const;

    bool complete() const;
    void setComplete(bool value);
    void setTime(int value);    
    int getTime() const;

private:
    QVector<QPointF> path;
    VelocityCalculator difficult;
    int _id = 1;
    int _time = 0;
    bool _complete = false;
};

#endif // ONEGAMEDATA_H
