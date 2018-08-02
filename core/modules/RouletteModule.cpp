#include "RouletteModule.h"

RouletteModule::RouletteModule(QObject *parent) : BaseModule(parent)
{ 
    prepareTimer  = new QTimer(this);
    connect(prepareTimer, SIGNAL(timeout()), this, SLOT(onPrepareTimerComplete()));

    mindwaveTimer = new QTimer(this);
    connect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));

    carInAnimation = new QPropertyAnimation(this);
    carInAnimation->setTargetObject(this);
    carInAnimation->setPropertyName("carY");
    connect(carInAnimation, SIGNAL(finished()), this, SLOT(onCarInAnimationCompleted()));
    carInAnimation->setStartValue(carInitialPosition);
    carInAnimation->setDuration(2000);
    carInAnimation->setEasingCurve(QEasingCurve::OutCubic);


    rollAnimation = new QPropertyAnimation(this);
    rollAnimation->setTargetObject(this);
    rollAnimation->setPropertyName("rotation");
    rollAnimation->setStartValue(0);
    rollAnimation->setDuration(2000);
    rollAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(rollAnimation, SIGNAL(finished()), this, SLOT(onRollAnimationCompleted()));

    scaleAnimation = new QPropertyAnimation(this);
    scaleAnimation->setTargetObject(this);
    scaleAnimation->setPropertyName("scale");
    scaleAnimation->setStartValue(0);
    scaleAnimation->setEndValue(1);
    scaleAnimation->setDuration(700);
    scaleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(scaleAnimation, SIGNAL(finished()), this, SLOT(onScaleAnimationCompleted()));
}

RouletteModule::~RouletteModule()
{
    if(carInAnimation)
    {
        disconnect(carInAnimation, SIGNAL(finished()), this, SLOT(onCarInAnimationCompleted()));
        delete carInAnimation;
    }

    if(rollAnimation)
    {
        disconnect(rollAnimation, SIGNAL(finished()), this, SLOT(onRollAnimationCompleted()));
        delete rollAnimation;
    }

    if(scaleAnimation)
    {
        disconnect(scaleAnimation, SIGNAL(finished()), this, SLOT(onScaleAnimationCompleted()));
        delete scaleAnimation;
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
    carMiddleThreshold = -config->mainConfig->touchScreen.height() / 2. - _carHeight * 0.5f;
    carTopThreshold = -config->mainConfig->touchScreen.height();

    carInAnimation->setEndValue(carMiddleThreshold);
}

void RouletteModule::start()
{
    qDebug()<<"======================= RouletteModule START =======================";

    connectComponents();
    choosenCategory = 0;
    setCarY(0.0);
    setRotation(0.0);
    setScale(0.0);
    setState(RouletteState::Intro);

    carInAnimation->setStartValue(0.0);
    carInAnimation->setEndValue(carMiddleThreshold);
    carInAnimation->start();
}

void RouletteModule::stop()
{
    qDebug()<<"======================= RouletteModule STOP =======================";

    disconnectComponents();
    setState(RouletteState::Intro);
    prepareTimer->stop();
    mindwaveTimer->stop();
    emit locationStopped();
}

void RouletteModule::onCarInAnimationCompleted()
{
    setState(RouletteState::Roll);
}

void RouletteModule::startRoll()
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
    rollAnimation->setEndValue(degrees);
    rollAnimation->start();
}

void RouletteModule::onRollAnimationCompleted()
{
    setState(RouletteState::RollFinished);
}

void RouletteModule::setState(RouletteState state)
{
    _state = state;
    emit stateChanged();

    if(_state == RouletteState::RollFinished)
    {
        qDebug()<<"choose user games!!!!!!";

        //serverComponent->startGameRequest(currentUser->baseUserData().id);
        onUserStartedGame();
    }
    else if(_state == RouletteState::CarStarting)
    {
        //mindwaveTimer->start(mindwaveTimerMills);
    }
}

void RouletteModule::onUserStartedGame()
{
    qDebug()<<"================ GAME STARTED!!!!!! ================";

    //prepareTimer->setSingleShot(true);
    //prepareTimer->start(prepareTimerDelay);
    scaleAnimation->start();

    //carInAnimation->setStartValue(carY());
   // carInAnimation->setEndValue(carY() + 100);
  //  carInAnimation->start();
}

void RouletteModule::onScaleAnimationCompleted()
{

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

float RouletteModule::rotation() const
{
    return _rotation;
}

void RouletteModule::setRotation(float value)
{
    _rotation = value;
    emit rotationChanged();
}

float RouletteModule::scale() const
{
    return _scale;
}

void RouletteModule::setScale(float value)
{
    _scale = value;
    emit scaleChanged();
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
