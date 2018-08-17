#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"


class AnimationManager : public QObject
{
    Q_OBJECT
public:
    explicit AnimationManager(QObject *parent = nullptr);

    void setQmlContext(QQmlContext* value);
    void setConfig(ConfigPtr value);

    Q_INVOKABLE QVariantList getAnimations() const;

private:
    QQmlContext* qmlContext;
    StandAnimConfig standAnimConfig;
    QVariantList animations;

};

#endif // ANIMATIONMANAGER_H
