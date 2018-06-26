#include "BaseComponent.h"

BaseComponent::BaseComponent(QObject *parent) : QObject(parent)
{

}

void BaseComponent::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
}
