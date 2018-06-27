#ifndef SERVERCOMPONENT_H
#define SERVERCOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "config/Config.h"

class ServerComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(ServerConfig config READ config WRITE setConfig NOTIFY configChanged)
public:
    explicit ServerComponent(QObject *parent = nullptr);

    void setConfig(const ServerConfig& config);
    ServerConfig config() const;

    virtual void start() override;
    virtual void setQmlContext(QQmlContext* value) override;
    virtual bool isHealthy() override;


    // REST API
//    void findUser(name, surname, mobile, email);
//    void saveUser();
//    void sendPIN();
//    void saveRFID();

//    void getStandConfig();
//    void getUserData();

//    void setUserProgress(stand, userId, stage, time, mindwaveData);

//    void healthCheck();
    
private:
     ServerConfig serverConfig;

signals:
    void configChanged();

public slots:
};

#endif // SERVERCOMPONENT_H
