#include "GameSession.h"
#include <QDateTime>
#include <QDebug>


GameSession::GameSession(QObject *parent) : QObject(parent)
{
    sessionTimer = new QTimer(this);
    connect(sessionTimer, SIGNAL(timeout()), this, SLOT(onSessionTimerUpdate()));
}

void GameSession::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("gameSession", this);
}

void GameSession::start()
{
    setCleanTime(0.);
    sessionStartTime = QDateTime::currentMSecsSinceEpoch();
    sessionTimer->start(sessionTimerMills);
}

void GameSession::stop()
{
    sessionTimer->stop();
    setSessionTime(0.);
    setCleanTime(0.);
}

void GameSession::addTaskTime(float time)
{
    setCleanTime(_cleanTime + time * toSeconds);
}

void GameSession::onSessionTimerUpdate()
{
    int newTime = QDateTime::currentMSecsSinceEpoch() - sessionStartTime;
    setSessionTime(newTime * toSeconds);
}

float GameSession::sessionTime() const
{
    return _sessionTime;
}

float GameSession::cleanTime() const
{
    return _cleanTime;
}

void GameSession::setSessionTime(float value)
{
    _sessionTime = value;
    emit sessionTimeChanged();
}

void GameSession::setCleanTime(float value)
{
    _cleanTime = value;
    emit cleanTimeChanged();
}
