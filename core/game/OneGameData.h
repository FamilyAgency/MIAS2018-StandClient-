#ifndef ONEGAMEDATA_H
#define ONEGAMEDATA_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QString>
#include "core/game/VelocityCalculator.h"

class OneGameData
{
public:
    explicit OneGameData();

    void setDescription(const QString& description);
    void setPath(const QVector<QPointF>& path);
    void setDifficult(const VelocityCalculator& value);
    void clearUserData();

    QVector<QPointF> getPath() const;
    VelocityCalculator getDifficult() const;

private:
    QVector<QPointF> path;
    QString description;
    VelocityCalculator difficult;

};

#endif // ONEGAMEDATA_H
