#ifndef ARDUINOCOMPONENT_H
#define ARDUINOCOMPONENT_H

#include <QObject>

class ArduinoComponent : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoComponent(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ARDUINOCOMPONENT_H
