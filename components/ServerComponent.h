#ifndef SERVERCOMPONENT_H
#define SERVERCOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "config/Config.h"

enum class ResponseType
{
    None,
    UserFetched
};
//Q_ENUMS(ResponseType)

struct ServerResponse
{
    ResponseType type = ResponseType::None;
    QString body;
};

class ServerComponent : public ExternalSystemComponent
{
    Q_OBJECT
    //Q_PROPERTY(ServerConfig config READ config WRITE setConfig NOTIFY configChanged)
public:
    explicit ServerComponent(QObject *parent = nullptr);

    virtual void setConfig(ConfigPtr config) override;
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
     virtual void fetchUser(int deviceId, int rfid);
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
    void serverResponse(const ServerResponse& response);

public slots:
};

#endif // SERVERCOMPONENT_H
