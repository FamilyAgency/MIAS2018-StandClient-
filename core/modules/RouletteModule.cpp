#include "RouletteModule.h"

RouletteModule::RouletteModule(QObject *parent) : BaseModule(parent)
{
    carStartTimer = new QTimer(this);
    connect(carStartTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));

    prepareTimer  = new QTimer(this);
    connect(prepareTimer, SIGNAL(timeout()), this, SLOT(onPrepareTimerComplete()));

    mindwaveTimer = new QTimer(this);
    connect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));
}

RouletteModule::~RouletteModule()
{
    if(carStartTimer)
    {
        carStartTimer->stop();
        disconnect(carStartTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete carStartTimer;
    }

    if(prepareTimer)
    {
        prepareTimer->stop();
        disconnect(prepareTimer, SIGNAL(timeout()), this, SLOT(onPrepareTimerComplete()));
        delete prepareTimer;
    }

    if(mindwaveTimer)
    {
        mindwaveTimer->stop();
        disconnect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));
        delete mindwaveTimer;
    }
}

void RouletteModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("rouletteModule", this);
}

void RouletteModule::setMindwave(QSharedPointer<MindwaveComponentBase> value)
{
    mindwaveComponent = value;
}

void RouletteModule::setServerComponent(QSharedPointer<ServerComponent> value)
{
    serverComponent = value;
}

void RouletteModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}

void RouletteModule::setConfig(ConfigPtr config)
{
    carMiddleThreshold = -config->mainConfig->touchScreen.height() / 2.;
    carTopThreshold = -config->mainConfig->touchScreen.height();
}

void RouletteModule::start()
{
    qDebug()<<"======================= RouletteModule START =======================";

    connectComponents();
    choosenCategory = 0;
    setState(RouletteState::Intro);
    setCarY(carInitialPosition);
    carStartTimer->start(carStartTimerMills);
}

void RouletteModule::stop()
{
    qDebug()<<"======================= RouletteModule STOP =======================";

    disconnectComponents();
    setState(RouletteState::Intro);
    carStartTimer->stop();
    prepareTimer->stop();
    mindwaveTimer->stop();
    emit locationStopped();
}

void RouletteModule::onUpdate()
{
    if(_carY > carMiddleThreshold - _carHeight * 0.5f)
    {
        setCarY(_carY + carDecriment);
    }
    else
    {
        carStartTimer->stop();
        setState(RouletteState::Roll);
    }
}

void RouletteModule::setState(RouletteState state)
{
    _state = state;
    emit stateChanged();

    if(_state == RouletteState::RollFinished)
    {
        qDebug()<<"choose user games!!!!!!";

        serverComponent->startGameRequest(currentUser->baseUserData().id);
    }
    else if(_state == RouletteState::CarStarting)
    {
        mindwaveTimer->start(mindwaveTimerMills);
    }
}

void RouletteModule::onUserStartedGame()
{
    qDebug()<<"================ GAME STARTED!!!!!! ================";

    prepareTimer->setSingleShot(true);
    prepareTimer->start(prepareTimerDelay);
}

void RouletteModule::createRollParams(float rollSpeed)
{
    if(choosenCategory != 0)
    {
        return;
    }

    int min = 0;
    int max = 2;
    choosenCategory = qrand() % ((max + 1) - min) + min;
    float degrees = 360;

    switch(choosenCategory)
    {
    case 0:
        degrees = 360 + 180;
        break;
    case 1:
        degrees = 360 + 270;
        break;
    case 2:
        degrees = 360 + 90;
        break;
    }

    qDebug()<<"choosenCategory============= "<<choosenCategory;

    emit gameCategoryUpdate(choosenCategory);
    emit rollParamsUpdate(degrees);
}

void RouletteModule::onPrepareTimerComplete()
{
    setState(RouletteState::CarStarting);
}

void RouletteModule::onMindwaveUpdate()
{
    if(mindwaveComponent->attention() > mindwaveAttentionThreshold)
    {
        if(_carY > carTopThreshold - _carHeight)
        {
            setCarY(_carY + carDecriment);
        }
        else
        {
            mindwaveTimer->stop();
            emit carStarting();
        }
    }
}

RouletteModule::RouletteState RouletteModule::state() const
{
    return _state;
}

float RouletteModule::carY() const
{
    return _carY;
}

void RouletteModule::setCarY(float value)
{
    _carY = value;
    emit carYChanged();
}

int RouletteModule::carHeight() const
{
    return _carHeight;
}

void RouletteModule::setCarHeight(int value)
{
    _carHeight = value;
    emit carHeightChanged();
}

QString RouletteModule::getName() const
{
    return "Roulette location";
}

void RouletteModule::connectComponents()
{
    if(serverComponent)
    {
        connect(serverComponent.data(), SIGNAL(userStartedGame()), this, SLOT(onUserStartedGame()));
    }
}

void RouletteModule::disconnectComponents()
{
    if(serverComponent)
    {
        disconnect(serverComponent.data(), SIGNAL(userStartedGame()), this, SLOT(onUserStartedGame()));
     }
}
