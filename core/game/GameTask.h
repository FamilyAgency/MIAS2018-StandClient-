#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QVector>
#include <QVector2D>
#include <QTimer>
#include "core/game/VelocityCalculator.h"
#include "components/MindwaveComponent.h"

class GameTask: public QObject
{
    Q_OBJECT

public:
    GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc);
    virtual ~GameTask();

    void setPath(const QVector<QPointF>& value);

    void init();
    void start();
    void stop();

    QPointF getStartPoint() const;    
    QPointF getCurPoint() const;
    QPointF getEndPoint() const;
    int getCompletionTime() const;

    void getCurrentPoint();
    QVariantList getCompletedPath() const;
    QVariantList getFullPath() const;
    float getForwardVectorRotation() const;

    float getMindwaveLimit() const;
    void setMindWaveClient(MindwaveComponent* value);

private:
    const int taskTimerMills = 10;

    MindwaveComponent* mindWave;

    QVector<QPointF> path;
    QPointF curPoint, startPoint, endPoint, position;
    int currentPointIndex = 0;   
    bool taskComplete = false;
    QVariantList completedPathList, fullPathList;
    QVector2D velocityDirection;

    VelocityCalculator velocityCalculator;

    void update(int humanValue);
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
