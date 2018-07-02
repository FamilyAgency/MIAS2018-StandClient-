#include "GameTask.h"
#include <QVector2D>
#include <QDebug>
#include <QtMath>
#include <QDateTime>

GameTask::GameTask()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    qDebug()<<"!!!!!!!!!!!!!Created game task!!!!!!!!!!!!!";
}

GameTask::GameTask(const QVector<QPointF>& value, const VelocityCalculator& velCalc)
{
    setData(value, velCalc);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    qDebug()<<"!!!!!!!!!!!!!Created game task!!!!!!!!!!!!!";
}

void GameTask::setData(const QVector<QPointF>& value, const VelocityCalculator& velCalc)
{
    path = value;
    fullPathList.clear();
    for(int i = 0; i<value.length(); i++)
    {
        fullPathList.append(value[i]);
    }

    velocityCalculator = velCalc;
}

GameTask::~GameTask()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
    delete timer;
    qDebug()<<"!!!!!!!!!!!!!destroyed game task!!!!!!!!!!!!!";
}

void GameTask::setPath(const QVector<QPointF>& value)
{
    path = value;
}

void GameTask::init()
{
    taskComplete = false;
    currentPointIndex = 0;
    completedPathList.clear();
    setPoints();
    addCompletedPoint(path[0]);
}

void GameTask::start()
{
    startTime = QDateTime::currentMSecsSinceEpoch();
    timer->start(taskTimerMills);
}

void GameTask::addCompletedPoint(const QPointF& point)
{
    completedPathList.append(point);
}

void GameTask::setPoints()
{
    startPoint = path[currentPointIndex];
    curPoint = startPoint;
    position = QPointF(0, 0);
    endPoint = path[currentPointIndex + 1];

    velocityDirection = QVector2D(endPoint - startPoint);
    velocityDirection.normalize();
}

void GameTask::setMindWaveClient(MindwaveComponent* value)
{
    mindWave = value;
}

void GameTask::onUpdate()
{
    int humanValue = 0;
    if(mindWave)
    {
        humanValue = mindWave->attention();
    }

    update(humanValue);

    emit updateEvent();
}

void GameTask::update(int humanValue)
{
    if(taskComplete)
    {
        return;
    }

    QVector2D vec(endPoint - curPoint);
    auto velocity = velocityCalculator.calculate(humanValue);
    const float epsilon = 1.1f * velocity;

    if(vec.length() < epsilon)
    {
        curPoint = endPoint;
        addCompletedPoint(curPoint);

        currentPointIndex++;

        if(currentPointIndex < path.length() - 1)
        {
            setPoints();
        }
        else
        {
            taskComplete = true;
            emit completeEvent();
        }
    }
    else
    {
        position.setX(position.x() + velocity);
        position.setY(position.y() + velocity);

        curPoint.setX(startPoint.x() + position.x() * velocityDirection.x());
        curPoint.setY(startPoint.y() + position.y() * velocityDirection.y());       
    }
}

float GameTask::getMindwaveLimit() const
{
    return velocityCalculator.getThreshold();
}

QVariantList GameTask::getCompletedPath() const
{
    return completedPathList;
}

QVariantList GameTask::getFullPath() const
{
    return fullPathList;
}

void GameTask::stop()
{
    timer->stop();
    completedPathList.clear();
}

int GameTask::getCompletionTime() const
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    return time;
}

QPointF GameTask::getStartPoint() const
{
    return startPoint;
}

QPointF GameTask::getCurPoint() const
{
    return curPoint;
}

QPointF GameTask::getEndPoint() const
{
    return path.last();
}

float GameTask::getForwardVectorRotation() const
{
    QVector2D forwardVec(endPoint - startPoint);
    return qAtan2(forwardVec.y(), forwardVec.x());
}

