#include "SuperGameModule.h"
#include <QDebug>
#include <QDateTime>

SuperGameModule::SuperGameModule(QObject *parent) : BaseModule(parent)
{
    superGameTimer = new QTimer(this);
    connect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

SuperGameModule::~SuperGameModule()
{
    if(superGameTimer)
    {
        disconnect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete superGameTimer;
    }
}

void SuperGameModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("superGameModule", this);
}

void SuperGameModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void SuperGameModule::start()
{
    qDebug()<<"======================= SuperGameModule START =======================";
}

void SuperGameModule::stop()
{
    qDebug()<<"======================= SuperGameModule STOP =======================";
    superGameTimer->stop();
}

void SuperGameModule::startGame()
{
    startTime = QDateTime::currentMSecsSinceEpoch();
    superGameTimer->start(superGameTimerMills);
}

void SuperGameModule::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int leftTime = superGameTime - time;
    if(leftTime >= 0.0)
    {
        emit updateSuperGameTime(leftTime);
    }
    else
    {
         superGameTimer->stop();
         emit updateSuperGameTime(0.0f);
         emit superGameFailed();
    }
}

QString SuperGameModule::getName() const
{
    return "Super Game location";
}

