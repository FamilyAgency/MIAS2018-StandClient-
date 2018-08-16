#include "GameCountDown.h"
#include <QDateTime>
#include <QDebug>

GameCountDown::GameCountDown()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

GameCountDown::~GameCountDown()
{
    if(timer)
    {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete timer;
    }
}

void GameCountDown::init()
{

}

void GameCountDown::run()
{
    startTime = QDateTime::currentMSecsSinceEpoch();
    timer->start(preTaskTimerMills);
}

void GameCountDown::stop()
{
     timer->stop();
}

void GameCountDown::onUpdate()
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
