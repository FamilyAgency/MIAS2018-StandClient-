#ifndef ROULETTEMODULE_H
#define ROULETTEMODULE_H

#include <QObject>
#include <QTimer>
#include "BaseModule.h"
#include "components/MindwaveComponent.h"

class RouletteModule : public BaseModule
{
    Q_OBJECT

    Q_PROPERTY(float carY READ carY WRITE setCarY NOTIFY carYChanged)
    Q_PROPERTY(RouletteState state READ state WRITE setState NOTIFY stateChanged)

public:
    enum class RouletteState
    {
        Intro,
        Roll,
        RollFinished,
        CarStarting
    };
    Q_ENUMS(RouletteState)

    explicit RouletteModule(QObject *parent = nullptr);
    virtual ~RouletteModule();

    Q_INVOKABLE void createRollParams(float rollSpeed);

    void setState(RouletteState state);
    RouletteState state() const;

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    void setMindwave(QSharedPointer<MindwaveComponent> value);

    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    float carY() const;
    void setCarY(float value);

private:
     const float carStartTimerMills = 100./60;
     const float mindwaveTimerMills = 100./60;
     const float prepareTimerDelay = 2000;

     const float carInitialPosition = 0.0f;
     const int carMiddleThreshold = -600;
     const float carDecriment = -1;
     const float carTopThreshold = -1200;

     const int mindwaveAttentionThreshold = 80;

     QTimer* carStartTimer = nullptr;
     QTimer* prepareTimer = nullptr;
     QTimer* mindwaveTimer = nullptr;

     QSharedPointer<MindwaveComponent> mindwaveComponent;
     RouletteState _state = RouletteState::Intro;

     float _carY = 0;
     int choosenCategory = 0;

signals:
     void carYChanged();
     void stateChanged();
     void locationStopped();
     void carStarting();
     void rollParamsUpdate(float degrees);

private slots:
     void onUpdate();
     void onPrepareTimerComplete();
     void onMindwaveUpdate();
};


#endif // ROULETTEMODULE_H