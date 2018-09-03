#ifndef GAMETASK_H
#define GAMETASK_H

#include <QObject>
#include <QVector>
#include <QVector2D>
#include <QTimer>
#include "core/game/VelocityCalculator.h"
#include "components/mindwave/MindwaveComponentBase.h"

class GameTask: public QObject
{
    Q_OBJECT

public:
    GameTask();
    GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc);
    virtual ~GameTask();

    void setPath(const QVector<QPointF>& value);
    void setData(const QVector<QPointF>& value, const VelocityCalculator& velCalc);

    void init();
    void start();
    void stop();

    QPointF getStartPoint() const;    
    QPointF getCurPoint() const;
    QPointF getEndPoint() const;
    int getCompletionTime() const;

   // void getCurrentPoint();
    QVariantList getCompletedPath() const;
    QVariantList getFullPath() const;
    float getForwardVectorRotation() const;
    QVector2D getForwardVector() const;

    float getMindwaveLimit() const;
    void setMindWaveClient(QSharedPointer<MindwaveComponentBase> value);

    QString getMetaData() const;

    void setRecording(bool value);

private:
    const int taskTimerMills = 10;

    QSharedPointer<MindwaveComponentBase> mindWave;

    QVector<QPointF> path;
    QPointF curPoint = QPointF(0.0f, 0.0f);
    QPointF startPoint, endPoint, position;
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

    bool isRecording = false;

    QString metaData = "";
    void addMetaData(int humanValue);

private slots:
     void onUpdate();
     void onAttentionChanged();

signals:
    void updateEvent();
    void completeEvent();
    void newCompletedPoint(const QPointF& point);

};

#endif // GAMETASK_H
