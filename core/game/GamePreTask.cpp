#include "GamePreTask.h"
#include <QDateTime>
#include <QDebug>

GamePreTask::GamePreTask(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

void GamePreTask::init()
{

}

void GamePreTask::run()
{
    startTime = QDateTime::currentMSecsSinceEpoch();
    timer->start(preTaskTimerMills);
}

void GamePreTask::stop()
{
     timer->stop();
}

void GamePreTask::onUpdate()
{
    int newTime = QDateTime::currentMSecsSinceEpoch() - startTime;

    if(newTime < preTaskMills)
    {
        emit update((preTaskMills - newTime) * toSeconds);
    }
    else
    {
        timer->stop();
        emit complete();
    }
}
