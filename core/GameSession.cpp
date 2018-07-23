#include "GameSession.h"
#include <QDateTime>
#include <QDebug>

GameSession::GameSession(QObject *parent) : QObject(parent)
{
    sessionTimer = new QTimer(this);
    connect(sessionTimer, SIGNAL(timeout()), this, SLOT(onSessionTimerUpdate()));
}

GameSession::~GameSession()
{
    if(sessionTimer)
    {
        disconnect(sessionTimer, SIGNAL(timeout()), this, SLOT(onSessionTimerUpdate()));
        delete sessionTimer;
    }
}

void GameSession::setQmlContext(QQmlContext* qmlContext)
{
    qmlContext->setContextProperty("gameSession", this);
}

void GameSession::start()
{
    sessionStartTime = QDateTime::currentMSecsSinceEpoch();
    sessionTimer->start(sessionTimerMills);
}

void GameSession::stop()
{
    sessionTimer->stop();
    setSessionTime(0.);
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

void GameSession::setSessionTime(float value)
{
    _sessionTime = value;
    emit sessionTimeChanged();
}
