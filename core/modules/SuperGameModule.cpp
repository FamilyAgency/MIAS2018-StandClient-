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

    gameTask.reset(new GameTask());
    connect(gameTask.data(), SIGNAL(updateEvent()), this, SLOT(onTaskUpdateEvent()));
    connect(gameTask.data(), SIGNAL(completeEvent()), this, SLOT(onTaskCompleteEvent()));
    connect(gameTask.data(), SIGNAL(newCompletedPoint(const QPointF&)), this, SLOT(onNewCompletedPoint(const QPointF&)));
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
    isRecording = config->mindwaveConfig->record;
    BaseModule::setConfig(config);
}

void SuperGameModule::setMindWaveClient(QSharedPointer<MindwaveComponentBase> value)
{
    //mindWave = value;
    gameTask->setMindWaveClient(value);
}

void SuperGameModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
}

void SuperGameModule::start()
{
    qDebug()<<"======================= SuperGameModule START =======================";
    connectComponents();

    setTaskRunning(false);

    auto superGameData = currentUser->getSuperGameData();
    gameTask->setRecording(isRecording);
    gameTask->setData(superGameData.getPath(), superGameData.getDifficult());

    superGameTime =  superGameData.getMaxTime();
    gameCompletedPath.clear();
    gameUncompletedPath = gameTask->getFullPath();

    emit updateSuperGameTime(superGameTime);
}

void SuperGameModule::stop()
{
    qDebug()<<"======================= SuperGameModule STOP =======================";
    disconnectComponents();
    gameTask->stop();
    superGameTimer->stop();
    gameCountDown->stop();
    gameTask->stop();
}

void SuperGameModule::onCountDownUpdate(float countDown)
{
   emit countDownUpdate(countDown);
}

void SuperGameModule::onCountDownComplete()
{
    startTime = QDateTime::currentMSecsSinceEpoch();   
    superGameTimer->start(superGameTimerMills);   
    gameTask->start();
    setTaskRunning(true);

    emit countDownComplete();
}

void SuperGameModule::onTaskUpdateEvent()
{
    emit updateCanvas();
}

void SuperGameModule::onNewCompletedPoint(const QPointF& point)
{
    gameCompletedPath.append(point);
}

void SuperGameModule::onTaskCompleteEvent()
{
    qDebug()<<"super game onTaskCompleteEvent";
    gameTask->stop();
    superGameTimer->stop();
    superGameWinTime = gameTask->getCompletionTime();
    serverComponent->finishGameRequest(currentUser->baseUserData().id);
}

void SuperGameModule::startGame()
{
    superGameWinTime = 0;
    gameTask->init();

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
        sendMetaData();
        gameTask->stop();
        superGameTimer->stop();
        emit updateSuperGameTime(0.0f);
        emit superGameFailed();
    }
}

void SuperGameModule::onUserFinishedGame()
{
    sendMetaData();

    currentUser->superGameCompleted(superGameWinTime);
    emit superGameSuccess(superGameWinTime);
}

void SuperGameModule::sendMetaData()
{
    if(isRecording)
    {
        currentUser->addMetaData(gameTask->getMetaData());
        currentUser->prepareMetaData();
        serverComponent->userMetaDataRequest(currentUser->baseUserData().id, currentUser->getMetaData());
    }
}

float SuperGameModule::getSuperGameTime() const
{
    return superGameTime;
}

float SuperGameModule::getPercent() const
{
    return percent;
}

void SuperGameModule::setTaskRunning(bool value)
{
    _taskRunning = value;
}

bool SuperGameModule::isRunning() const
{
    return _taskRunning;
}

bool SuperGameModule::isPreTaskState() const
{
    return !_taskRunning;
}

QVariantList SuperGameModule::getCompletedPath() const
{
   return gameCompletedPath;
}

QVariantList SuperGameModule::getGameUncompletedPath() const
{
   return gameUncompletedPath;
}

float SuperGameModule::getMindwaveLimit() const
{
    return gameTask->getMindwaveLimit();
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

QPointF SuperGameModule::getStartPoint() const
{
    return gameTask->getStartPoint();
}

QPointF SuperGameModule::getCurPoint() const
{
    return gameTask->getCurPoint();
}

float SuperGameModule::getForwardVectorRotation() const
{
    return gameTask->getForwardVectorRotation();
}

QVector2D SuperGameModule::getForwardVector() const
{
    return gameTask->getForwardVector();
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
    gameTask->stop();
    superGameTimer->stop();
    emit updateSuperGameTime(0.0f);
    emit superGameFailed();
}


