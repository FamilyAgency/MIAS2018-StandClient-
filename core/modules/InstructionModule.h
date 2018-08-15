#ifndef INSTRUCTIONMODULE_H
#define INSTRUCTIONMODULE_H

#include <QObject>
#include <QTimer>
#include "BaseModule.h"
#include "components/mindwave/MindwaveComponentBase.h"

class InstructionModule : public BaseModule
{
    Q_OBJECT

    Q_PROPERTY(float opacity1 READ opacity1 WRITE setOpacity1 NOTIFY opacity1Changed)
    Q_PROPERTY(float opacity2 READ opacity2 WRITE setOpacity2 NOTIFY opacity2Changed)

public:
    explicit InstructionModule(QObject *parent = nullptr);
    virtual ~InstructionModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;

    void setMindwave(QSharedPointer<MindwaveComponentBase> value);


    virtual QString getName() const override;
    Q_INVOKABLE void mediaEnded();

    float opacity1() const;
    void setOpacity1(float value);

    float opacity2() const;
    void setOpacity2(float value);

private:
    QTimer* delayReadTimer = nullptr;
    QTimer* animDelayTimer = nullptr;
    QTimer* showTextTimer = nullptr;

    const float delayTimerMills = 10000.0f;
    const float animDelayTimerMills = 1500.0f;

    QSharedPointer<MindwaveComponentBase> mindWaveComponent;

    QPropertyAnimation* opacity1Animator = nullptr;
    QPropertyAnimation* opacity2Animator = nullptr;
    QList<QPropertyAnimation*> animations;

    float _opacity1 = 0;
    float _opacity2 = 0;

    enum class TextAnimated
    {
        Text1,
        Text2
    }
    textAnimated;

signals:
    void instructionComplete();
    void mindwaveReady();

    void opacity1Changed();
    void opacity2Changed();

private slots:
    void onDelayTimerComplete();
    void onAnimDelayTimerComplete();
    void onShownTextComplete();

    void onOpacity1AnimatorCompleted();

};

#endif // INSTRUCTIONMODULE_H
