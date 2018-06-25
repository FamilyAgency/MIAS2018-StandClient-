#ifndef HEALTHCHECKERCOMPONENT_H
#define HEALTHCHECKERCOMPONENT_H

#include <QObject>
#include "ArduinoComponent.h"
#include "MindwaveComponent.h"

class HealthCheckerComponent : public QObject
{
    Q_OBJECT
public:
    explicit HealthCheckerComponent(ArduinoComponent* arduinoComponent, MindwaveComponent* mindWaveComponent);

signals:

public slots:
};

#endif // HEALTHCHECKERCOMPONENT_H
