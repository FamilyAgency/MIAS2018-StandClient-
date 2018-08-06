#include "RouletteModule.h"

RouletteModule::RouletteModule(QObject *parent) : BaseModule(parent)
{ 
    prepareTimer  = new QTimer(this);
    connect(prepareTimer, SIGNAL(timeout()), this, SLOT(onPrepareTimerComplete()));

    mindwaveTimer = new QTimer(this);
    connect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));


    mainTitleOpacityAnimation = new QPropertyAnimation(this);
    mainTitleOpacityAnimation->setTargetObject(this);
    mainTitleOpacityAnimation->setPropertyName("mainTitleOpacity");
    mainTitleOpacityAnimation->setStartValue(0);
    mainTitleOpacityAnimation->setEndValue(1);
    mainTitleOpacityAnimation->setDuration(700);
    mainTitleOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

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


    carYAnimation2 = new QPropertyAnimation(this);
    carYAnimation2->setTargetObject(this);
    carYAnimation2->setPropertyName("carY");
    carYAnimation2->setDuration(2000);
    carYAnimation2->setEasingCurve(QEasingCurve::OutCubic);




    taskOpacityAnimation = new QPropertyAnimation(this);
    taskOpacityAnimation->setTargetObject(this);
    taskOpacityAnimation->setPropertyName("taskOpacity");
    taskOpacityAnimation->setStartValue(0);
    taskOpacityAnimation->setEndValue(1);
    //  connect(carYAnimation2, SIGNAL(finished()), this, SLOT(onCarInAnimationCompleted()));
    taskOpacityAnimation->setDuration(2000);
    taskOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);

    readTaskTimer = new QTimer(this);
    connect(readTaskTimer, SIGNAL(timeout()), this, SLOT(onReadTaskTimerCompleted()));
    readTaskTimer->setSingleShot(true);
    readTaskTimer->setInterval(3000);


    carYAnimation3 = new QPropertyAnimation(this);
    carYAnimation3->setTargetObject(this);
    carYAnimation3->setPropertyName("carY");
    carYAnimation3->setDuration(2000);
    carYAnimation3->setEasingCurve(QEasingCurve::OutCubic);


    scaleAnimation2 = new QPropertyAnimation(this);
    scaleAnimation2->setTargetObject(this);
    scaleAnimation2->setPropertyName("scale");
    scaleAnimation2->setStartValue(1);
    scaleAnimation2->setEndValue(0.9);
    scaleAnimation2->setDuration(700);
    scaleAnimation2->setEasingCurve(QEasingCurve::InOutQuad);


    circleFinalYAnimation = new QPropertyAnimation(this);
    circleFinalYAnimation->setTargetObject(this);
    circleFinalYAnimation->setPropertyName("circleY");
    circleFinalYAnimation->setStartValue(222);
    circleFinalYAnimation->setEndValue(300);
    circleFinalYAnimation->setDuration(700);
    circleFinalYAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(circleFinalYAnimation, SIGNAL(finished()), this, SLOT(onCircleFinalYAnimationCompleted()));




    helpTextAnimation = new QPropertyAnimation(this);
    helpTextAnimation->setTargetObject(this);
    helpTextAnimation->setPropertyName("helpTextOpacity");
    helpTextAnimation->setStartValue(0);
    helpTextAnimation->setEndValue(1);
    helpTextAnimation->setDuration(700);
    helpTextAnimation->setEasingCurve(QEasingCurve::InOutQuad);


    pulsarAnimation = new QPropertyAnimation(this);
    pulsarAnimation->setTargetObject(this);
    pulsarAnimation->setPropertyName("pulsarScale");
    pulsarAnimation->setStartValue(0);
    pulsarAnimation->setLoopCount(3);
    pulsarAnimation->setEndValue(1);
    pulsarAnimation->setDuration(2500);
    pulsarAnimation->setEasingCurve(QEasingCurve::InOutExpo);
    connect(pulsarAnimation, SIGNAL(finished()), this, SLOT(onPulsarAnimationCompleted()));



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
    carYAnimation2->setStartValue(carMiddleThreshold);
    carYAnimation2->setEndValue(carMiddleThreshold + 220);
    carYAnimation3->setStartValue(carMiddleThreshold + 220);
    carYAnimation3->setEndValue(carMiddleThreshold + 120);
}

void RouletteModule::start()
{
    qDebug()<<"======================= RouletteModule START =======================";


    connectComponents();

    setParticlesVisibility(true);
    choosenCategory = 0;
    setCarY(0.0);
    setRotation(0.0);
    setScale(0.0);
    setState(RouletteState::Intro);

    mainTitleOpacityAnimation->setStartValue(0);
    mainTitleOpacityAnimation->setEndValue(1);
    mainTitleOpacityAnimation->start();

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
    scaleAnimation->setStartValue(0);
    scaleAnimation->setEndValue(1);
    scaleAnimation->start();

    mainTitleOpacityAnimation->setStartValue(1);
    mainTitleOpacityAnimation->setEndValue(0);
    mainTitleOpacityAnimation->start();


    //carInAnimation->setStartValue(carY());
    // carInAnimation->setEndValue(carY() + 100);
    //  carInAnimation->start();
}

void RouletteModule::onScaleAnimationCompleted()
{
    carYAnimation2->start();
    taskOpacityAnimation->setStartValue(0);
    taskOpacityAnimation->setEndValue(1);
    taskOpacityAnimation->start();
    readTaskTimer->start();
}

void RouletteModule::onReadTaskTimerCompleted()
{
    taskOpacityAnimation->setStartValue(1);
    taskOpacityAnimation->setEndValue(0);
    taskOpacityAnimation->start();
    carYAnimation3->start();

    scaleAnimation2->start();
    circleFinalYAnimation->start();
    setParticlesVisibility(false);
}

void RouletteModule::onCircleFinalYAnimationCompleted()
{
    helpTextAnimation->start();
    pulsarAnimation->start();
    qDebug()<<"======================= onCircleFinalYAnimationCompleted =======================";

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

float RouletteModule::mainTitleOpacity() const
{
    return _mainTitleOpacity;
}

void RouletteModule::setMainTitleOpacity(float value)
{
    _mainTitleOpacity = value;
    emit mainTitleOpacityChanged();
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

float RouletteModule::taskOpacity() const
{
    return _taskOpacity;
}

void RouletteModule::setTaskOpacity(float value)
{
    _taskOpacity = value;
    emit taskOpacityChanged();
}

float RouletteModule::circleY() const
{
    return _circleY;
}

void RouletteModule::setCircleY(float value)
{
    _circleY = value;
    emit circleYChanged();
}

float RouletteModule::helpTextOpacity() const
{
    return _helpTextOpacity;
}

void RouletteModule::setHelpTextOpacity(float value)
{
    _helpTextOpacity = value;
    emit helpTextOpacityChanged();
}


bool RouletteModule::particlesVisibility() const
{
    return _particlesVisibility;
}

void RouletteModule::setParticlesVisibility(bool value)
{
    _particlesVisibility = value;
    emit particlesVisibilityChanged();
}

float RouletteModule::pulsarScale() const
{
    return _pulsarScale;
}

void RouletteModule::setPulsarScale(float value)
{
    _pulsarScale = value;
    emit pulsarScaleChanged();
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
