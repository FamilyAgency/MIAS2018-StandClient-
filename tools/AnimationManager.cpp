#include "AnimationManager.h"
#include <QVariant>

AnimationManager::AnimationManager(QObject *parent) : QObject(parent)
{

}

void AnimationManager::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("animationManager", this);
}

void AnimationManager::setConfig(ConfigPtr value)
{
    standAnimConfig = *value->standAnimConfig;
    for(auto anim : standAnimConfig.animations)
    {
        animations.append(QVariant::fromValue(anim));
    }
}

QVariantList AnimationManager::getAnimations() const
{
    return animations;
}
