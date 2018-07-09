#ifndef SERVERCOMPONENT_H
#define SERVERCOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "config/Config.h"
#include "network/http/HTTPClient.h"

enum class ResponseType
{
    None,
    Error,
    UserFetched,
    Logout
};

enum class ServerErrorType
{
    None,
    TimeOut,
    NetworkError,
    ServerIsDown
};

struct ServerResponse
{
    ResponseType type = ResponseType::None;
    ServerErrorType errorType = ServerErrorType::None;
    QString body;

    void clear()
    {
        type = ResponseType::None;
        errorType = ServerErrorType::None;
        body = "";
    }
};

class ServerComponent : public ExternalSystemComponent
{
    Q_OBJECT
    Q_PROPERTY(ServerConfig serverConfig READ serverConfig WRITE setServerConfig NOTIFY serverConfigChanged)

    Q_ENUMS(LoginError)
    Q_ENUMS(ServerStatus)

public:
    explicit ServerComponent(QObject *parent = nullptr);
    virtual ~ServerComponent();

    enum class ServerStatus
    {
        Free,
        Busy,
        Error
    };

    enum class LoginError
    {
        UserDoesntExist,
        WasRecently,
        ServerError,
        ArduinoError,
        Undefined
    };

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr config) override;   

    virtual void start() override;
    virtual void stop() override;
    virtual bool isHealthy() override;

    ServerConfig serverConfig() const;
    void setServerConfig(const ServerConfig& );

    Q_INVOKABLE void setServerStatus(ServerStatus serverStatus);


// REST API
//   -----------------config-----------------
//   void getStandConfig(int deviceId);
//   void checkUpdates(int deviceId);

//   rfid ?= id
//   -----------------user-----------------
     virtual void fetchUser(int rfid);
     virtual void logout();
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

    friend class ServerComponentTest;
    
private:
     ServerConfig _serverConfig;
     QSharedPointer<HTTPClient> httpClient;
     ServerStatus _serverStatus = ServerStatus::Free;
     bool canRunRequest() const;

     ServerResponse response;

signals:
    void serverConfigChanged();
    void serverStatusChanged(const ServerStatus& status);
    void serverResponse(const ServerResponse& response);
    void serverError();

protected slots:
   void httpRequestSuccessHandler(const QString& data);
   void httpRequestFailedHandler(const QString& data);
};

#endif // SERVERCOMPONENT_H
