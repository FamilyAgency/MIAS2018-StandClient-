#include "RouletteModule.h"
#include "tools/MathTools.h"
#include <algorithm>

RouletteModule::RouletteModule(QObject *parent) : BaseModule(parent)
{
    mindwaveTimer = new QTimer(this);
    connect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));

    mainTitleOpacityAnimation = new QPropertyAnimation(this);
    mainTitleOpacityAnimation->setTargetObject(this);
    mainTitleOpacityAnimation->setPropertyName("mainTitleOpacity");
    mainTitleOpacityAnimation->setStartValue(0);
    mainTitleOpacityAnimation->setEndValue(1);
    mainTitleOpacityAnimation->setDuration(700);
    mainTitleOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(mainTitleOpacityAnimation);

    carInAnimation = new QPropertyAnimation(this);
    carInAnimation->setTargetObject(this);
    carInAnimation->setPropertyName("carY");
    connect(carInAnimation, SIGNAL(finished()), this, SLOT(onCarInAnimationCompleted()));
    carInAnimation->setStartValue(carInitialPosition);
    carInAnimation->setDuration(2000);
    carInAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(carInAnimation);

    rollAnimation = new QPropertyAnimation(this);
    rollAnimation->setTargetObject(this);
    rollAnimation->setPropertyName("rotation");
    rollAnimation->setStartValue(0);
    rollAnimation->setDuration(2000);
    rollAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    animations.push_back(rollAnimation);
    connect(rollAnimation, SIGNAL(finished()), this, SLOT(onRollAnimationCompleted()));

    scaleAnimation = new QPropertyAnimation(this);
    scaleAnimation->setTargetObject(this);
    scaleAnimation->setPropertyName("scale");
    scaleAnimation->setStartValue(0);
    scaleAnimation->setEndValue(1);
    scaleAnimation->setDuration(700);
    scaleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    animations.push_back(scaleAnimation);
    connect(scaleAnimation, SIGNAL(finished()), this, SLOT(onScaleAnimationCompleted()));

    carYAnimation2 = new QPropertyAnimation(this);
    carYAnimation2->setTargetObject(this);
    carYAnimation2->setPropertyName("carY");
    carYAnimation2->setDuration(2000);
    carYAnimation2->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(carYAnimation2);

    taskOpacityAnimation = new QPropertyAnimation(this);
    taskOpacityAnimation->setTargetObject(this);
    taskOpacityAnimation->setPropertyName("taskOpacity");
    taskOpacityAnimation->setStartValue(0);
    taskOpacityAnimation->setEndValue(1);
    taskOpacityAnimation->setDuration(700);
    taskOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(taskOpacityAnimation);

    mainIconOpacityAnimation = new QPropertyAnimation(this);
    mainIconOpacityAnimation->setTargetObject(this);
    mainIconOpacityAnimation->setPropertyName("mainIconOpacity");
    mainIconOpacityAnimation->setStartValue(0);
    mainIconOpacityAnimation->setEndValue(1);
    mainIconOpacityAnimation->setDuration(700);
    mainIconOpacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(mainIconOpacityAnimation);

    mainIconScaleAnimation = new QPropertyAnimation(this);
    mainIconScaleAnimation->setTargetObject(this);
    mainIconScaleAnimation->setPropertyName("mainIconScale");
    mainIconScaleAnimation->setStartValue(0);
    mainIconScaleAnimation->setEndValue(1);
    mainIconScaleAnimation->setDuration(1000);
    mainIconScaleAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(mainIconScaleAnimation);

    mainIconYAnimation = new QPropertyAnimation(this);
    mainIconYAnimation->setTargetObject(this);
    mainIconYAnimation->setPropertyName("mainIconY");
    mainIconYAnimation->setStartValue(0);
    mainIconYAnimation->setEndValue(1);
    mainIconYAnimation->setDuration(2000);
    mainIconYAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(mainIconYAnimation);

    allIconsScaleAnimation = new QPropertyAnimation(this);
    allIconsScaleAnimation->setTargetObject(this);
    allIconsScaleAnimation->setPropertyName("allIconsScale");
    allIconsScaleAnimation->setStartValue(0);
    allIconsScaleAnimation->setEndValue(1);
    allIconsScaleAnimation->setDuration(700);
    allIconsScaleAnimation->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(allIconsScaleAnimation);

    readTaskTimer = new QTimer(this);
    connect(readTaskTimer, SIGNAL(timeout()), this, SLOT(onReadTaskTimerCompleted()));
    readTaskTimer->setSingleShot(true);
    readTaskTimer->setInterval(3000);

    carYAnimation3 = new QPropertyAnimation(this);
    carYAnimation3->setTargetObject(this);
    carYAnimation3->setPropertyName("carY");
    carYAnimation3->setDuration(2000);
    carYAnimation3->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(carYAnimation3);

    scaleAnimation2 = new QPropertyAnimation(this);
    scaleAnimation2->setTargetObject(this);
    scaleAnimation2->setPropertyName("scale");
    scaleAnimation2->setStartValue(1);
    scaleAnimation2->setEndValue(0.9);
    scaleAnimation2->setDuration(700);
    scaleAnimation2->setEasingCurve(QEasingCurve::InOutQuad);
    animations.push_back(scaleAnimation2);

    circleFinalYAnimation = new QPropertyAnimation(this);
    circleFinalYAnimation->setTargetObject(this);
    circleFinalYAnimation->setPropertyName("circleY");
    circleFinalYAnimation->setStartValue(circleYDefault);
    circleFinalYAnimation->setEndValue(circleYDefault + 80);
    circleFinalYAnimation->setDuration(700);
    circleFinalYAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    connect(circleFinalYAnimation, SIGNAL(finished()), this, SLOT(onCircleFinalYAnimationCompleted()));
    animations.push_back(circleFinalYAnimation);

    helpTextAnimation = new QPropertyAnimation(this);
    helpTextAnimation->setTargetObject(this);
    helpTextAnimation->setPropertyName("helpTextOpacity");
    helpTextAnimation->setStartValue(0);
    helpTextAnimation->setEndValue(1);
    helpTextAnimation->setDuration(700);
    helpTextAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    animations.push_back(helpTextAnimation);

    pulsarAnimation = new QPropertyAnimation(this);
    pulsarAnimation->setTargetObject(this);
    pulsarAnimation->setPropertyName("pulsarScale");
    pulsarAnimation->setStartValue(0);
    pulsarAnimation->setLoopCount(1);
    pulsarAnimation->setEndValue(1);
    pulsarAnimation->setDuration(1500);
    pulsarAnimation->setEasingCurve(QEasingCurve::OutExpo);
    animations.push_back(pulsarAnimation);
    connect(pulsarAnimation, SIGNAL(finished()), this, SLOT(onPulsarAnimationCompleted()));

    circleOpacityAnimation = new QPropertyAnimation(this);
    circleOpacityAnimation->setTargetObject(this);
    circleOpacityAnimation->setPropertyName("circleOpacity");
    circleOpacityAnimation->setStartValue(1);
    circleOpacityAnimation->setEndValue(0);
    circleOpacityAnimation->setDuration(700);
    circleOpacityAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    animations.push_back(circleOpacityAnimation);
    connect(circleOpacityAnimation, SIGNAL(finished()), this, SLOT(onCircleOpacityCompleted()));

    carYAnimation4 = new QPropertyAnimation(this);
    carYAnimation4->setTargetObject(this);
    carYAnimation4->setPropertyName("carY");
    carYAnimation4->setDuration(5000);
    carYAnimation4->setEasingCurve(QEasingCurve::Linear);
    animations.push_back(carYAnimation4);

    mindwaveCtrlOpacityAnimation = new QPropertyAnimation(this);
    mindwaveCtrlOpacityAnimation->setTargetObject(this);
    mindwaveCtrlOpacityAnimation->setPropertyName("mindwaveCtrlOpacity");
    mindwaveCtrlOpacityAnimation->setDuration(1000);
    mindwaveCtrlOpacityAnimation->setEasingCurve(QEasingCurve::Linear);
    mindwaveCtrlOpacityAnimation->setStartValue(0);
    mindwaveCtrlOpacityAnimation->setEndValue(1);
    animations.push_back(mindwaveCtrlOpacityAnimation);

    smallCarTimer = new QTimer(this);
    connect(smallCarTimer, SIGNAL(timeout()), this, SLOT(onSmallCarUpdate()));

    smallCarPrepareTimer = new QTimer(this);
    connect(smallCarPrepareTimer, SIGNAL(timeout()), this, SLOT(onStartSmallCarAnimation()));

}

RouletteModule::~RouletteModule()
{
    disconnect(carInAnimation, SIGNAL(finished()), this, SLOT(onCarInAnimationCompleted()));
    disconnect(rollAnimation, SIGNAL(finished()), this, SLOT(onRollAnimationCompleted()));
    disconnect(scaleAnimation, SIGNAL(finished()), this, SLOT(onScaleAnimationCompleted()));
    disconnect(circleFinalYAnimation, SIGNAL(finished()), this, SLOT(onCircleFinalYAnimationCompleted()));
    disconnect(pulsarAnimation, SIGNAL(finished()), this, SLOT(onPulsarAnimationCompleted()));
    disconnect(circleOpacityAnimation, SIGNAL(finished()), this, SLOT(onCircleOpacityCompleted()));

    for (auto &anim : animations)
    {
        if(anim)
        {
            delete anim;
        }
    }
    animations.clear();

    if(mindwaveTimer)
    {
        mindwaveTimer->stop();
        disconnect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));
        delete mindwaveTimer;
    }

    if(readTaskTimer)
    {
        readTaskTimer->stop();
        disconnect(readTaskTimer, SIGNAL(timeout()), this, SLOT(onReadTaskTimerCompleted()));
        delete readTaskTimer;
    }


    if(smallCarTimer)
    {
        smallCarTimer->stop();
        disconnect(smallCarTimer, SIGNAL(timeout()), this, SLOT(onSmallCarUpdate()));
        delete smallCarTimer;
    }

    if(smallCarTimer)
    {
        smallCarPrepareTimer->stop();
        disconnect(smallCarPrepareTimer, SIGNAL(timeout()), this, SLOT(onStartSmallCarAnimation()));
        delete smallCarPrepareTimer;
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

void RouletteModule::setGameComplexity(QSharedPointer<GameComplexityData> value)
{
    gameComplexityData = value;
}

void RouletteModule::setConfig(ConfigPtr config)
{
    carMiddleThreshold = - config->mainConfig->touchScreen.height() / 2. - _carHeight * 0.5f - 60.0f;
    carTopThreshold = -config->mainConfig->touchScreen.height();

    carInAnimation->setEndValue(carMiddleThreshold);
    carYAnimation2->setStartValue(carMiddleThreshold);
    const int shiftY = 450;
    carYAnimation2->setEndValue(carMiddleThreshold + shiftY);
    carYAnimation3->setStartValue(carMiddleThreshold + shiftY);
    carYAnimation3->setEndValue(carMiddleThreshold + 110);
    BaseModule::setConfig(config);
}

void RouletteModule::start()
{
    qDebug()<<"======================= RouletteModule START =======================";

    mindwaveAttentionThreshold = gameComplexityData->roulette;
    emit mindwaveAttentionThresholdUpdate(mindwaveAttentionThreshold);

    connectComponents();
    initParams();
    mainTitleOpacityAnimation->start();
    carInAnimation->start();

    //test
    // emit gameCategoryUpdate(0);
    //  mindwaveTimer->start(mindwaveTimerMills);
}

void RouletteModule::initParams()
{  
    setParticlesVisibility(true);
    choosenCategory = 0;
    setCarY(0.0);
    setRotation(0.0);
    setScale(0.0);
    setCircleOpacity(1.0);
    setCircleY(circleYDefault);
    setTaskOpacity(0.0);
    setMindwaveCtrlOpacity(0.0);

    setHelpTextOpacity(0.0f);

    setPulsarScale(0.0f);

    setMainIconVisibility(false);
    setMainIconOpacity(1.0f);
    setMainIconY(0.0f);
    setMainIconScale(1.0f);

    setAllIconsScale(0.0f);

    mainTitleOpacityAnimation->setStartValue(0);
    mainTitleOpacityAnimation->setEndValue(1);

    carInAnimation->setStartValue(0.0);
    carInAnimation->setEndValue(carMiddleThreshold);
}

void RouletteModule::stop()
{
    qDebug()<<"======================= RouletteModule STOP =======================";

    disconnectComponents();

    mindwaveTimer->stop();
    readTaskTimer->stop();
    smallCarTimer->stop();
    smallCarPrepareTimer->stop();

    for (auto &anim : animations)
    {
        anim->stop();
    }
}

void RouletteModule::onCarInAnimationCompleted()
{
    allIconsScaleAnimation->setStartValue(0.0);
    allIconsScaleAnimation->setEndValue(1.0);
    allIconsScaleAnimation->start();
}

void RouletteModule::startRoll()
{
    if(choosenCategory != 0)
    {
        return;
    }

    if(categoryIndex >= maxCategories)
    {
        std::random_shuffle(categories.begin(), categories.end());
        categoryIndex = 0;
    }

    // categoryIndex = 2;

    choosenCategory = categories[categoryIndex];

    qDebug()<<"categoryIndex: "<<categoryIndex;
    qDebug()<<"vector: "<<categories;
    qDebug()<<"choosenCategory: "<<choosenCategory;

    //choosenCategory = MathTools::randomInRange(0, 2);
    // choosenCategory = MathTools::clamp(choosenCategory, 0, 2);
    float degrees = 360;

    QString iconPath = "";

    switch(choosenCategory)
    {
    case 0:
        degrees = 360 + 90;//task1
        iconPath = "task1/icon.png";
        break;
    case 1:
        degrees = 360 + 270;//task3
        iconPath = "task2/icon.png";
        break;
    case 2:
        degrees = 360 + 180;//task2
        iconPath = "task3/icon.png";
        break;
    }

    emit updateChoosenCategoryImagePath(iconPath);
    emit gameCategoryUpdate(choosenCategory);
    rollAnimation->setEndValue(degrees);
    rollAnimation->start();
    categoryIndex++;
}

void RouletteModule::onRollAnimationCompleted()
{
    serverComponent->startGameRequest(currentUser->baseUserData().id);
   // onUserStartedGame();
}

void RouletteModule::onUserStartedGame()
{
    qDebug()<<"================ GAME STARTED!!!!!! ================";

    setMainIconVisibility(true);

    allIconsScaleAnimation->setStartValue(1.0);
    allIconsScaleAnimation->setEndValue(0.0);
    allIconsScaleAnimation->start();

    scaleAnimation->setStartValue(0);
    scaleAnimation->setEndValue(1);
    scaleAnimation->start();

    mainTitleOpacityAnimation->setStartValue(1);
    mainTitleOpacityAnimation->setEndValue(0);
    mainTitleOpacityAnimation->start();
}

void RouletteModule::onScaleAnimationCompleted()
{
    emit startCarMasking();

    carYAnimation2->start();
    taskOpacityAnimation->setStartValue(0);
    taskOpacityAnimation->setEndValue(1);
    taskOpacityAnimation->start();

    mainIconScaleAnimation->setStartValue(1);
    mainIconScaleAnimation->setEndValue(0.7);
    mainIconScaleAnimation->start();

    mainIconYAnimation->setStartValue(0);
    mainIconYAnimation->setEndValue(120);
    mainIconYAnimation->start();

    readTaskTimer->start();
}

void RouletteModule::onReadTaskTimerCompleted()
{
    taskOpacityAnimation->setStartValue(1);
    taskOpacityAnimation->setEndValue(0);
    taskOpacityAnimation->start();
    carYAnimation3->start();

    mainIconOpacityAnimation->setStartValue(1);
    mainIconOpacityAnimation->setEndValue(0);
    mainIconOpacityAnimation->start();

    scaleAnimation2->start();
    circleFinalYAnimation->start();
    setParticlesVisibility(false);
}

void RouletteModule::onCircleFinalYAnimationCompleted()
{
    helpTextAnimation->setStartValue(0);
    helpTextAnimation->setEndValue(1);
    helpTextAnimation->start();

    onPulsarAnimationCompleted();
   // pulsarAnimation->start();
}

void RouletteModule::onPulsarAnimationCompleted()
{
    emit endCarMasking();
    circleOpacityAnimation->start();
}

void RouletteModule::onCircleOpacityCompleted()
{
    mindwaveCtrlOpacityAnimation->setStartValue(0);
    mindwaveCtrlOpacityAnimation->setEndValue(1);
    mindwaveCtrlOpacityAnimation->start();
    emit showMindwaveControls();
    // mindwaveTimer->start(mindwaveTimerMills);
}

void RouletteModule::onMindwaveUpdate()
{
    //    if(mindwaveComponent->attention() > mindwaveAttentionThreshold)
    //    {
    //        if(_carY > carTopThreshold - _carHeight * 0.5)
    //        {
    //            setCarY(_carY + carDecriment);
    //        }
    //        else if(_carY <= carTopThreshold)
    //        {
    //            mindwaveTimer->stop();
    //            //startSmallCarAnimation();
    //        }
    //    }
}

void RouletteModule::finalizeCarAnimation()
{
    qDebug()<<"finalize car animation";

    //helpTextAnimation->setStartValue(1);
   // helpTextAnimation->setEndValue(0);
   // helpTextAnimation->start();

    carYAnimation4->setStartValue(_carY);
    carYAnimation4->setEndValue(-1920 - _carHeight);
    carYAnimation4->start();

    smallCarPrepareTimer->start(smallCarPrepareTimerMills);

   // mindwaveCtrlOpacityAnimation->setEndValue(0);
   // mindwaveCtrlOpacityAnimation->start();
}

void RouletteModule::onStartSmallCarAnimation()
{
    smallCarPrepareTimer->stop();

    startPoint = currentUser->gameUserData().startPath[0];// QPointF(420, 2010);
    curPoint = startPoint;
    position = QPointF(0, 0);
    endPoint = currentUser->gameUserData().startPath[1];//QPointF( 449, 1708);

    velocityDirection = QVector2D(endPoint - startPoint);
    velocityDirection.normalize();

    emit showSmallCar();
    smallCarTimer->start(smallCarTimerMills);
}

void RouletteModule::onSmallCarUpdate()
{
    QVector2D vec(endPoint - curPoint);
    auto velocity = 1.5;
    const float epsilon = 1.1f * velocity;

    if(vec.length() < epsilon)
    {
        smallCarTimer->stop();
        emit carStarting();
    }
    else
    {
        // setCarY(_carY + carDecriment);

        position.setX(position.x() + velocity);
        position.setY(position.y() + velocity);

        curPoint.setX(startPoint.x() + position.x() * velocityDirection.x());
        curPoint.setY(startPoint.y() + position.y() * velocityDirection.y());
        emit updateCanvas();
    }
}

QPointF RouletteModule::getCurPoint() const
{
    return curPoint;
}

float RouletteModule::getForwardVectorRotation() const
{
    QVector2D forwardVec(endPoint - startPoint);
    return qAtan2(forwardVec.y(), forwardVec.x());
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

float RouletteModule::circleOpacity() const
{
    return _circleOpacity;
}

void RouletteModule::setCircleOpacity(float value)
{
    _circleOpacity = value;
    emit circleOpacityChanged();
}

bool RouletteModule::mainIconVisibility() const
{
    return _mainIconVisibility;
}

void RouletteModule::setMainIconVisibility(bool value)
{
    _mainIconVisibility = value;
    emit mainIconVisibilityChanged();
}

float RouletteModule::mainIconScale() const
{
    return _mainIconScale;
}

void RouletteModule::setAllIconsScale(float value)
{
    _allIconsScale = value;
    emit allIconsScaleChanged();
}

float RouletteModule::allIconsScale() const
{
    return _allIconsScale;
}

void RouletteModule::setMainIconScale(float value)
{
    _mainIconScale = value;
    emit mainIconScaleChanged();
}

float RouletteModule::mainIconOpacity() const
{
    return _mainIconOpacity;
}

void RouletteModule::setMainIconOpacity(float value)
{
    _mainIconOpacity = value;
    emit mainIconOpacityChanged();
}

float RouletteModule::mainIconY() const
{
    return _mainIconY;
}

void RouletteModule::setMainIconY(float value)
{
    _mainIconY = value;
    emit mainIconYChanged();
}


float RouletteModule::mindwaveCtrlOpacity() const
{
    return _mindwaveCtrlOpacity;
}

void RouletteModule::setMindwaveCtrlOpacity(float value)
{
    _mindwaveCtrlOpacity = value;
    emit mindwaveCtrlOpacityChanged();
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
