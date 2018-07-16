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

void RouletteModule::setMindwave(QSharedPointer<MindwaveComponent> value)
{
    mindwaveComponent = value;
}

void RouletteModule::start()
{
    choosenCategory = 0;
    setState(RouletteState::Intro);
    setCarY(carInitialPosition);
    carStartTimer->start(carStartTimerMills);
}

void RouletteModule::stop()
{
    setState(RouletteState::Intro);
    carStartTimer->stop();
    prepareTimer->stop();
    mindwaveTimer->stop();
    emit locationStopped();
}

void RouletteModule::onUpdate()
{
    if(_carY > carMiddleThreshold)
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
        prepareTimer->setSingleShot(true);
        prepareTimer->start(prepareTimerDelay);
    }
    else if(_state == RouletteState::CarStarting)
    {
        mindwaveTimer->start(mindwaveTimerMills);
    }
}

void RouletteModule::createRollParams(float rollSpeed)
{
    if(choosenCategory != 0)
    {
        return;
    }

    int min = 1;
    int max = 3;
    choosenCategory = qrand() % ((max + 1) - min) + min;
    float degrees = 360;

    switch(choosenCategory)
    {
    case 1:
        degrees = 360 + 90;
        break;
    case 2:
        degrees = 360 + 270;
        break;
    case 3:
        degrees = 360;
        break;
    }

    qDebug()<<"choosenCategory============= "<<choosenCategory;

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
        if(_carY > carTopThreshold)
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

QString RouletteModule::getName() const
{
    return "Roulette location";
}
