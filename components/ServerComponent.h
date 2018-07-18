#ifndef SERVERCOMPONENT_H
#define SERVERCOMPONENT_H

#include <QObject>
#include "components/ExternalSystemComponent.h"
#include "config/Config.h"
#include "network/http/HTTPClient.h"
#include "core/data/UserData.h"

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

    enum class ResponseType
    {
        None,
        Error,
        UserFetched,
        Logout,

        SearchUserByIdRequest,
        ConfigRequest,
        UpdatesRequest,
        HealthLogRequest,
        AllUsersRequest,
        CreateUserRequest,
        SearchUserRequest,
        DeleteAllTestUsersRequest,
        VerifyUserRequest,
        ConfirmUserRequest,
        ConfirmPrizeRequest
    };
    Q_ENUMS(ResponseType)

    enum class ServerGlobalErrorType
    {
        None,
        TimeOut,
        NetworkError,
        ServerIsDown
    };
    Q_ENUMS(ServerGlobalErrorType)

    struct ServerResponse
    {
        ResponseType type = ResponseType::None;
        ServerGlobalErrorType errorType = ServerGlobalErrorType::None;
        QString body;
        QString status = "";
        int code = 0;

        void clear()
        {
            type = ResponseType::None;
            errorType = ServerGlobalErrorType::None;
            body = "";
        }
    };

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr config) override;   

    virtual void start() override;
    virtual void stop() override;
    virtual bool isHealthy() override;

    ServerConfig serverConfig() const;
    void setServerConfig(const ServerConfig& );

    Q_INVOKABLE void setServerStatus(ServerStatus serverStatus);

    virtual void parse(const ServerResponse& response);
    virtual void logout();


    friend class ServerComponentTest;

protected:
     ServerResponse response;
     ServerConfig _serverConfig;
     QSharedPointer<HTTPClient> httpClient;
     ServerStatus _serverStatus = ServerStatus::Free;
     bool canRunRequest() const;

signals:
    void serverConfigChanged();
    void serverStatusChanged(const ServerStatus& status);
    void serverResponse(const ServerResponse& response);

    void serverRequestError(ResponseType responseType);
    void serverRequestSuccess(ResponseType responseType);
    void serverGlobalError(ServerGlobalErrorType globalErrorType);

    void serverLogged(const QString& log);


    void newUserEntered(const UserObject&);
    void userNotFound();    
    void userAlreadyExists();

protected slots:
   virtual void httpRequestSuccessHandler(const QString& data);
   virtual void httpRequestFailedHandler(const QString& data);
};

typedef ServerComponent::ServerResponse ServerResponse;

#endif // SERVERCOMPONENT_H
