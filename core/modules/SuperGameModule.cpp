#include "SuperGameModule.h"
#include <QDebug>
#include <QDateTime>

SuperGameModule::SuperGameModule(QObject *parent) : BaseModule(parent)
{
    superGameTimer = new QTimer(this);
    connect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    gameCountDown.reset(new GameCountDown());
    connect(gameCountDown.data(), SIGNAL(update(float)), this, SLOT(onCountDownUpdate(float)));
    connect(gameCountDown.data(), SIGNAL(complete()), this, SLOT(onCountDownComplete()));
}

SuperGameModule::~SuperGameModule()
{
    if(superGameTimer)
    {
        disconnect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete superGameTimer;
    }

    disconnect(gameCountDown.data(), SIGNAL(update(float)), this, SLOT(onCountDownUpdate(float)));
    disconnect(gameCountDown.data(), SIGNAL(complete()), this, SLOT(onCountDownComplete()));
}

void SuperGameModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("superGameModule", this);
}

void SuperGameModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}

void SuperGameModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void SuperGameModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
}

void SuperGameModule::start()
{
    qDebug()<<"======================= SuperGameModule START =======================";
    connectComponents();
    superGameTime = currentUser->getSuperGameData().time;
    emit updateSuperGameTime(superGameTime);
}

void SuperGameModule::stop()
{
    qDebug()<<"======================= SuperGameModule STOP =======================";
    disconnectComponents();
    superGameTimer->stop();
    gameCountDown->stop();
}

void SuperGameModule::onCountDownUpdate(float countDown)
{
    emit countDownUpdate(countDown);
}

void SuperGameModule::onCountDownComplete()
{
    emit countDownComplete();
    superGameTimer->start(superGameTimerMills);
}

void SuperGameModule::startGame()
{
    superGameWinTime = 0;
    startTime = QDateTime::currentMSecsSinceEpoch();
    gameCountDown->init();
    gameCountDown->run();
    emit superGameStarted();
}

void SuperGameModule::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int leftTime = superGameTime - time;

    percent = float(leftTime)/superGameTime;

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

void SuperGameModule::onUserFinishedGame()
{
    currentUser->superGameCompleted(superGameWinTime);
    emit superGameSuccess(superGameWinTime);
}


float SuperGameModule::getSuperGameTime() const
{
    return superGameTime;
}

float SuperGameModule::getPercent() const
{
    return percent;
}

QString SuperGameModule::getName() const
{
    return "Super Game location";
}

void SuperGameModule::connectComponents()
{
    if(serverComponent)
    {
        connect(serverComponent.data(), SIGNAL(userFinishedGame()), this, SLOT(onUserFinishedGame()));
    }
}

void SuperGameModule::disconnectComponents()
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(userFinishedGame()), this, SLOT(onUserFinishedGame()));
    }
}

//===================TESTS===================

void SuperGameModule::superGamePassedTest()
{
    superGameTimer->stop();
    superGameWinTime = QDateTime::currentMSecsSinceEpoch() - startTime;
    serverComponent->finishGameRequest(currentUser->baseUserData().id);
}

void SuperGameModule::superGameFailedTest()
{
    superGameTimer->stop();
    emit updateSuperGameTime(0.0f);
    emit superGameFailed();
}


