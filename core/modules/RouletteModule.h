#ifndef ROULETTEMODULE_H
#define ROULETTEMODULE_H

#include <QObject>
#include <QTimer>
#include <QVector2D>

#include "BaseModule.h"
#include "components/mindwave/MindwaveComponentBase.h"
#include "components/ServerComponent.h"

class RouletteModule : public BaseModule
{
    Q_OBJECT

    Q_PROPERTY(float carY READ carY WRITE setCarY NOTIFY carYChanged)
    Q_PROPERTY(float rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(int carHeight READ carHeight WRITE setCarHeight NOTIFY carHeightChanged)
    Q_PROPERTY(float mainTitleOpacity READ mainTitleOpacity WRITE setMainTitleOpacity NOTIFY mainTitleOpacityChanged)
    Q_PROPERTY(float taskOpacity READ taskOpacity WRITE setTaskOpacity NOTIFY taskOpacityChanged)
    Q_PROPERTY(float circleY READ circleY WRITE setCircleY NOTIFY circleYChanged)
    Q_PROPERTY(float helpTextOpacity READ helpTextOpacity WRITE setHelpTextOpacity NOTIFY helpTextOpacityChanged)
    Q_PROPERTY(bool particlesVisibility READ particlesVisibility WRITE setParticlesVisibility NOTIFY particlesVisibilityChanged)
    Q_PROPERTY(float pulsarScale READ pulsarScale WRITE setPulsarScale NOTIFY pulsarScaleChanged)
    Q_PROPERTY(float circleOpacity READ circleOpacity WRITE setCircleOpacity NOTIFY circleOpacityChanged)

    Q_PROPERTY(bool mainIconVisibility READ mainIconVisibility WRITE setMainIconVisibility NOTIFY mainIconVisibilityChanged)
    Q_PROPERTY(float mainIconScale READ mainIconScale WRITE setMainIconScale NOTIFY mainIconScaleChanged)
    Q_PROPERTY(float mainIconOpacity READ mainIconOpacity WRITE setMainIconOpacity NOTIFY mainIconOpacityChanged)
    Q_PROPERTY(float mainIconY READ mainIconY WRITE setMainIconY NOTIFY mainIconYChanged)

    Q_PROPERTY(float allIconsScale READ allIconsScale WRITE setAllIconsScale NOTIFY allIconsScaleChanged)

public:
    explicit RouletteModule(QObject *parent = nullptr);
    virtual ~RouletteModule();

    Q_INVOKABLE void startRoll();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;

    void setMindwave(QSharedPointer<MindwaveComponentBase> value);
    void setServerComponent(QSharedPointer<ServerComponent> value);
    void setUser(QSharedPointer<UserData> value);


    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    float carY() const;
    void setCarY(float value);

    float rotation() const;
    void setRotation(float value);

    float scale() const;
    void setScale(float value);

    int carHeight() const;
    void setCarHeight(int value);

    float taskOpacity() const;
    void setTaskOpacity(float value);

    float circleY() const;
    void setCircleY(float value);

    float helpTextOpacity() const;
    void setHelpTextOpacity(float value);

    bool particlesVisibility() const;
    void setParticlesVisibility(bool value);

    float mainTitleOpacity() const;
    void setMainTitleOpacity(float value);

    float pulsarScale() const;
    void setPulsarScale(float value);

    float circleOpacity() const;
    void setCircleOpacity(float value);


    bool mainIconVisibility() const;
    void setMainIconVisibility(bool value);

    float mainIconScale() const;
    void setMainIconScale(float value);

    float mainIconOpacity() const;
    void setMainIconOpacity(float value);

    float mainIconY() const;
    void setMainIconY(float value);

    float allIconsScale() const;
    void setAllIconsScale(float value);

    Q_INVOKABLE QPointF getCurPoint() const;
    Q_INVOKABLE float getForwardVectorRotation() const;

private:
    QPropertyAnimation* mainTitleOpacityAnimation = nullptr;
    QPropertyAnimation* carInAnimation = nullptr;
    QPropertyAnimation* rollAnimation = nullptr;
    QPropertyAnimation* scaleAnimation = nullptr;
    QPropertyAnimation* carYAnimation2 = nullptr;
    QPropertyAnimation* taskOpacityAnimation = nullptr;
    QPropertyAnimation* carYAnimation3 = nullptr;
    QPropertyAnimation* scaleAnimation2 = nullptr;
    QPropertyAnimation* circleFinalYAnimation = nullptr;
    QPropertyAnimation* helpTextAnimation = nullptr;
    QPropertyAnimation* pulsarAnimation = nullptr;
    QPropertyAnimation* circleOpacityAnimation = nullptr;

    QPropertyAnimation* mainIconOpacityAnimation = nullptr;
    QPropertyAnimation* mainIconScaleAnimation = nullptr;
    QPropertyAnimation* mainIconYAnimation = nullptr;
    QPropertyAnimation* allIconsScaleAnimation = nullptr;



    QList<QPropertyAnimation*> animations;

    const float mindwaveTimerMills = 100.0f/60.0f;
    const float prepareTimerDelay = 2000.0f;

    const float carInitialPosition = 0.0f;
    int carMiddleThreshold = -850;
    int carTopThreshold = -1200;
    const float carDecriment = -1.0f;
    const float circleYDefault = 418;
    const int mindwaveAttentionThreshold = 80;

    const int smallCarTimerMills = 10;


    QTimer* mindwaveTimer = nullptr;
    QTimer* readTaskTimer = nullptr;
    QTimer* smallCarTimer = nullptr;

    QSharedPointer<MindwaveComponentBase> mindwaveComponent;
    QSharedPointer<ServerComponent> serverComponent;
    QSharedPointer<UserData> currentUser;

    float _mainTitleOpacity  = 0.0f;
    float _scale = 0;
    float _carY = 0;
    float _rotation = 0;
    int _carHeight = 555;
    int choosenCategory = 0;

    float _taskOpacity = 0;
    float _circleY = circleYDefault;
    float _helpTextOpacity = 0.0;
    bool _particlesVisibility = true;
    float _pulsarScale = 0.0;
    float _circleOpacity = 1;

    bool _mainIconVisibility = false;
    float _mainIconScale = 1;
    float _mainIconOpacity = 1;
    float _mainIconY = 1;
    float _allIconsScale = 1;

    void initParams();
    void connectComponents();
    void disconnectComponents();

    void startSmallCarAnimation();

    QPointF curPoint = QPointF(0.0f, 0.0f);
    QPointF startPoint, endPoint, position;
    QVector2D velocityDirection;


signals:
    void mainTitleOpacityChanged();
    void carYChanged();
    void rotationChanged();
    void stateChanged();
    void carStarting();
    void gameCategoryUpdate(int id);
    void carHeightChanged();
    void scaleChanged();
    void taskOpacityChanged();
    void circleYChanged();
    void helpTextOpacityChanged();
    void particlesVisibilityChanged();
    void pulsarScaleChanged();
    void circleOpacityChanged();
    void showBrb();


    void mainIconVisibilityChanged();
    void mainIconScaleChanged();
    void mainIconOpacityChanged();
    void mainIconYChanged();


    void allIconsScaleChanged();
    void showSmallCar();

    void updateCanvas();


private slots:
    void onMindwaveUpdate();
    void onUserStartedGame();

    void onCarInAnimationCompleted();
    void onRollAnimationCompleted();
    void onScaleAnimationCompleted();


    void onReadTaskTimerCompleted();
    void onCircleFinalYAnimationCompleted();
    void onPulsarAnimationCompleted();
    void onCircleOpacityCompleted();
    void onSmallCarUpdate();
};


#endif // ROULETTEMODULE_H
