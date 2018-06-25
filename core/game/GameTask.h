#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QVector>
#include <QVector2D>
#include <QTimer>
#include "core/game/VelocityCalculator.h"

class GameTask: public QObject
{
    Q_OBJECT

public:
    GameTask();
    GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc);
    void setPath(const QVector<QPointF>& value);

    void init();
    void start();
    void stop();

    void update(int humanValue);    

    QPointF getStartPoint() const;    
    QPointF getCurPoint() const;
    QPointF getEndPoint() const;
    int getCompletionTime() const;

    void getCurrentPoint();
    //QVector<QPointF> getCompletedPath() const;
    QVariantList getCompletedPath() const;
    QVariantList getFullPath() const;
   // QVector<QPointF> getFullPath() const;
    float getForwardVectorRotation() const;

    float getMindwaveLimit() const;
private:
    QVector<QPointF> path;
    QPointF curPoint, startPoint, endPoint, position;
    int currentPointIndex = 0;   
    bool taskComplete = false;
    //QVector<QPointF> completedPath, fullPath;
    QVariantList completedPathList, fullPathList;
    QVector2D velocityDirection;

    VelocityCalculator velocityCalculator;

    void setPoints();
    void addCompletedPoint(const QPointF& point);

    QTimer* timer;

    int startTime;

private slots:
     void onUpdate();

signals:
    void updateEvent();
    void completeEvent();

};

#endif // GAMETASK_H
