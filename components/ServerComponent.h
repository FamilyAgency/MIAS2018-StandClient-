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
//   -----------------config-----------------
//   void getStandConfig(int deviceId);
//   void checkUpdates(int deviceId);

//   rfid ?= id
//   -----------------user-----------------
//   void fetchUser(int deviceId, int rfid)
//   void saveUserProgress(int deviceId, int userId, int stage, int cleanTime, data[] mindwaveData)


//   -----------------reg-----------------
//    void findUser(int deviceId, name, surname, mobile, email);
//    void sendUser(int deviceId, name, surname, mobile, email, pinNeeded);
//    void sendPin(int deviceId,int)
//    void writeRFID(int deviceId, userId);


//   -----------------prize-----------------
//   void fetchUser(int deviceId, int rfid)


//   -----------------tools-----------------
//    void healthCheck(deviceId);
    
private:
     ServerConfig serverConfig;

signals:
    void configChanged();

public slots:
};

#endif // SERVERCOMPONENT_H
