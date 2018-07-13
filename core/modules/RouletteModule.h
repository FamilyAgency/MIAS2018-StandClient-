#ifndef ROULETTEMODULE_H
#define ROULETTEMODULE_H

#include <QObject>
#include <QTimer>
#include "BaseModule.h"

class RouletteModule : public BaseModule
{
    Q_OBJECT

    Q_PROPERTY(float carY READ carY WRITE setCarY NOTIFY carYChanged)

public:
    enum class RouletteState
    {
        Intro,
        Roll,
        RollFinished
    };
    Q_ENUMS(RouletteState)

    explicit RouletteModule(QObject *parent = nullptr);
    virtual ~RouletteModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    float carY() const;
    void setCarY(float value);

private:
     QTimer* carStartTimer = nullptr;
     int _carY = 0;

signals:
     void carYChanged();
     void rouletteStateChanged(RouletteState state);

private slots:
     void onUpdate();
};


#endif // ROULETTEMODULE_H
