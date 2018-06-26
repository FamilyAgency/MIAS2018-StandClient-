#ifndef HEALTHCHECKERCOMPONENT_H
#define HEALTHCHECKERCOMPONENT_H

#include <QObject>
#include "ArduinoComponent.h"
#include "MindwaveComponent.h"

class HealthCheckerComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit HealthCheckerComponent(QObject *parent = nullptr);
    void addComponent(BaseComponent* component);

private:
     QList<BaseComponent*> components;

signals:

public slots:
};

#endif // HEALTHCHECKERCOMPONENT_H
