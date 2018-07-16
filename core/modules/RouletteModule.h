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
     QTimer* carStartTimer = nullptr;
     QTimer* prepareTimer = nullptr;
     QTimer* mindwaveTimer = nullptr;

     QSharedPointer<MindwaveComponent> mindwaveComponent;
     RouletteState _state = RouletteState::Intro;

     int _carY = 0;

signals:
     void carYChanged();
     void stateChanged();
     void locationStopped();
     void carStarting();

private slots:
     void onUpdate();
     void onPrepareTimerComplete();
     void onMindwaveUpdate();

};


#endif // ROULETTEMODULE_H
