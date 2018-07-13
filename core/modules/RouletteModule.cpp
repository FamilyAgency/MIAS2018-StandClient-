#include "RouletteModule.h"

RouletteModule::RouletteModule(QObject *parent) : BaseModule(parent)
{
    carStartTimer = new QTimer(this);
    connect(carStartTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

RouletteModule::~RouletteModule()
{
    if(carStartTimer)
    {
        carStartTimer->stop();
        disconnect(carStartTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete carStartTimer;
    }
}

void RouletteModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("rouletteModule", this);
}

void RouletteModule::start()
{
    emit rouletteStateChanged(RouletteState::Intro);
    setCarY(0);
    carStartTimer->start(100/60.);
}

void RouletteModule::stop()
{
    carStartTimer->stop();
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
        emit rouletteStateChanged(RouletteState::Roll);
    }
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
