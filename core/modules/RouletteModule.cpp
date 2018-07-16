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
    setState(RouletteState::Intro);
    setCarY(0);
    carStartTimer->start(100/60.);
}

void RouletteModule::stop()
{
    carStartTimer->stop();
    prepareTimer->stop();
    mindwaveTimer->stop();
    emit locationStopped();
}

void RouletteModule::onUpdate()
{
    if(_carY > -600)
    {
        setCarY(_carY - 1);
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
        prepareTimer->setSingleShot(true);
        prepareTimer->start(2000);
    }
    else if(_state == RouletteState::CarStarting)
    {
        mindwaveTimer->start(100/60.);
    }
}

void RouletteModule::onPrepareTimerComplete()
{
    setState(RouletteState::CarStarting);
}

void RouletteModule::onMindwaveUpdate()
{
    if(mindwaveComponent->attention() > 80)
    {
        if(_carY > -1200)
        {
            setCarY(_carY - 1);
        }
        else
        {
            //ready to go
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
