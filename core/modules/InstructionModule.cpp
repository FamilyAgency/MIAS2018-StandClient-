#include "InstructionModule.h"

InstructionModule::InstructionModule(QObject *parent) : BaseModule(parent)
{
    delayReadTimer = new QTimer(this);
    connect(delayReadTimer, SIGNAL(timeout()), this, SLOT(onDelayTimerComplete()));

    animDelayTimer = new QTimer(this);
    connect(animDelayTimer, SIGNAL(timeout()), this, SLOT(onAnimDelayTimerComplete()));

    showTextTimer = new QTimer(this);
    connect(showTextTimer, SIGNAL(timeout()), this, SLOT(onShownTextComplete()));

    instructionEndTimer = new QTimer(this);
    connect(instructionEndTimer, SIGNAL(timeout()), this, SLOT(onInstructionEndTimerComplete()));

    mindwaveTimer = new QTimer(this);
    connect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));

    opacity1Animator = new QPropertyAnimation(this);
    opacity1Animator->setTargetObject(this);
    opacity1Animator->setPropertyName("opacity1");
    opacity1Animator->setStartValue(0);
    opacity1Animator->setEndValue(1);
    opacity1Animator->setDuration(2000);
    opacity1Animator->setEasingCurve(QEasingCurve::OutCubic);
    connect(opacity1Animator, SIGNAL(finished()), this, SLOT(onOpacity1AnimatorCompleted()));
    animations.push_back(opacity1Animator);

    opacity2Animator = new QPropertyAnimation(this);
    opacity2Animator->setTargetObject(this);
    opacity2Animator->setPropertyName("opacity2");
    opacity2Animator->setStartValue(0);

    opacity2Animator->setEndValue(1);
    opacity2Animator->setDuration(2000);
    opacity2Animator->setEasingCurve(QEasingCurve::OutCubic);
    animations.push_back(opacity2Animator);
}

InstructionModule::~InstructionModule()
{    
    if(delayReadTimer)
    {
        delayReadTimer->stop();
        disconnect(delayReadTimer, SIGNAL(timeout()), this, SLOT(onDelayTimerComplete()));
        delete delayReadTimer;
    }

    if(animDelayTimer)
    {
        animDelayTimer->stop();
        disconnect(animDelayTimer, SIGNAL(timeout()), this, SLOT(onAnimDelayTimerComplete()));
        delete animDelayTimer;
    }

    if(showTextTimer)
    {
        showTextTimer->stop();
        disconnect(showTextTimer, SIGNAL(timeout()), this, SLOT(onShownTextComplete()));
        delete showTextTimer;
    }

    if(mindwaveTimer)
    {
        disconnect(mindwaveTimer, SIGNAL(timeout()), this, SLOT(onMindwaveUpdate()));
        delete mindwaveTimer;
    }


    disconnect(opacity1Animator, SIGNAL(finished()), this, SLOT(onOpacity1AnimatorCompleted()));

    for (auto &anim : animations)
    {
        if(anim)
        {
            delete anim;
        }
    }

    animations.clear();

    if(instructionEndTimer)
    {
        instructionEndTimer->stop();
        disconnect(instructionEndTimer, SIGNAL(timeout()), this, SLOT(onInstructionEndTimerComplete()));
        delete instructionEndTimer;
    }
}

void InstructionModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("instructionModule", this);
}

void InstructionModule::setGameComplexity(QSharedPointer<GameComplexityData> value)
{
    gameComplexityData = value;
}

void InstructionModule::start()
{
    qDebug()<<"======================= InstructionModule START =======================";

    textAnimated = TextAnimated::Text1;
    setOpacity1(0.0f);
    setOpacity2(0.0f);

    mindwaveAttentionThreshold = gameComplexityData->instruction;
    qDebug()<<"gameComplexityData->instruction "<<mindwaveAttentionThreshold;
    delayReadTimer->start(delayTimerMills);
}

void InstructionModule::stop()
{
    qDebug()<<"======================= InstructionModule STOP =======================";
    delayReadTimer->stop();
    animDelayTimer->stop();
    showTextTimer->stop();
    instructionEndTimer->stop();
    mindwaveTimer->stop();

    for (auto &anim : animations)
    {
        anim->stop();
    }
}

void InstructionModule::setMindwave(QSharedPointer<MindwaveComponentBase> value)
{
    mindWaveComponent = value;
}

void InstructionModule::onDelayTimerComplete()
{
    delayReadTimer->stop();
    mindwaveTimer->start();
}

void InstructionModule::onMindwaveUpdate()
{
    if(mindWaveComponent->attention() > mindwaveAttentionThreshold)
    {
        mindwaveTimer->stop();

        emit mindwaveReady();
        animDelayTimer->start(animDelayTimerMills);
        instructionEndTimer->start(instructionEndTimerMills);
    }
}

void InstructionModule::onAnimDelayTimerComplete()
{
    animDelayTimer->stop();

    textAnimated = TextAnimated::Text1;
    opacity1Animator->setStartValue(0);
    opacity1Animator->setEndValue(1);
    opacity1Animator->setDuration(500);
    opacity1Animator->start();

    showTextTimer->start(1200);
}

void InstructionModule::onShownTextComplete()
{
    showTextTimer->stop();

    if(textAnimated == TextAnimated::Text1)
    {
        opacity1Animator->setStartValue(1);
        opacity1Animator->setEndValue(0);
        opacity1Animator->setDuration(500);
        opacity1Animator->start();
    }
    else
    {
        opacity2Animator->setStartValue(1);
        opacity2Animator->setEndValue(0);
        opacity2Animator->setDuration(500);
        opacity2Animator->start();
    }
}

void InstructionModule::onOpacity1AnimatorCompleted()
{
    if(opacity1() == 0.0f)
    {
        textAnimated = TextAnimated::Text2;
        showTextTimer->start(3300);

        opacity2Animator->setStartValue(0);
        opacity2Animator->setEndValue(1);
        opacity2Animator->setDuration(500);
        opacity2Animator->start();


        //test
        //mediaEnded();
    }
}

void InstructionModule::onInstructionEndTimerComplete()
{
    instructionEndTimer->start();
    emit instructionComplete();
}

float InstructionModule::opacity1() const
{
    return _opacity1;
}

void InstructionModule::setOpacity1(float value)
{
    _opacity1 = value;
    emit opacity1Changed();
}

float InstructionModule::opacity2() const
{
    return _opacity2;
}

void InstructionModule::setOpacity2(float value)
{
    _opacity2 = value;
    emit opacity2Changed();
}

void InstructionModule::mediaEnded()
{
    emit instructionComplete();
}

QString InstructionModule::getName() const
{
    return "Instructions location";
}

