#ifndef ONEGAMEDATA_H
#define ONEGAMEDATA_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QString>
#include "core/game/VelocityCalculator.h"
#include "config/Config.h"

class OneGameData
{
public:
    explicit OneGameData();

    void setDescription(const QString& description);
    void setPath(const QVector<QPointF>& path);
    void setDifficult(const VelocityCalculator& value);
    void setAdvantage(const OneAdvantageConfig& value);

    void clearUserData();

    QVector<QPointF> getPath() const;
    VelocityCalculator getDifficult() const;
    OneAdvantageConfig getAdvantage() const;

    void setId(int value);
    int getId() const;

    bool complete() const;
    void setComplete(bool value);
    void setTime(int value);    
    int getTime() const;

private:
    QVector<QPointF> path;
    QString description;
    VelocityCalculator difficult;
    OneAdvantageConfig advantage;
    int featureId = 1;
    int _id = 1;
    int _time = 0;
    bool _complete = false;
};

#endif // ONEGAMEDATA_H
