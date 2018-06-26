#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <QObject>
#include <QQmlContext>

class BaseComponent : public QObject
{
    Q_OBJECT
public:
    explicit BaseComponent(QObject *parent = nullptr);
    virtual void setQmlContext(QQmlContext* value);

protected:
    QQmlContext* qmlContext;

signals:

public slots:
};

#endif // BASECOMPONENT_H
