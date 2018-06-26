#ifndef SERVERCOMPONENT_H
#define SERVERCOMPONENT_H

#include <QObject>
#include "components/BaseComponent.h"
#include "config/Config.h"

class ServerComponent : public BaseComponent
{
    Q_OBJECT
    Q_PROPERTY(ServerConfig config READ config WRITE setConfig NOTIFY configChanged)
public:
    explicit ServerComponent(QObject *parent = nullptr);

    void setConfig(const ServerConfig& config);
    ServerConfig config() const;

    virtual void setQmlContext(QQmlContext* value) override;


private:
     ServerConfig serverConfig;

signals:
    void configChanged();

public slots:
};

#endif // SERVERCOMPONENT_H
