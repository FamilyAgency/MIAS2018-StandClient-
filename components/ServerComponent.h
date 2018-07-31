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

public:
    explicit ServerComponent(QObject *parent = nullptr);
    virtual ~ServerComponent();

    enum class ServerStatus
    {
        Free,
        Busy,
        Error
    };
    Q_ENUM(ServerStatus)

    enum class HTTPMethod
    {
        GET,
        POST,
        PUT,
        DELETE
    };

    enum class RegErrorType
    {
        UserAlreadyExists = 555,
        UserAlreadyConfirmed = 556
    };

    enum class ResponseType
    {
        None,
        Error,

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
        ConfirmPrizeRequest,

        StartGameRequest,
        UpdateGameRequest,
        FinishGameRequest
    };
    Q_ENUM(ResponseType)

    enum class ServerGlobalErrorType
    {
        None,
        TimeOut,
        NetworkError,
        ServerIsDown
    };
    Q_ENUM(ServerGlobalErrorType)

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

    Q_INVOKABLE void setServerStatus(ServerStatus serverStatus);
    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr config) override;

    virtual void startGameRequest(int userId) = 0;
    virtual void updateGameRequest(int userId) = 0;
    virtual void finishGameRequest(int userId) = 0;
    virtual void searchUserByIdRequest(int userId) = 0;
    ServerConfig serverConfig() const;
    void setServerConfig(const ServerConfig& );

protected:
    ServerResponse response;
    ServerConfig _serverConfig;
    QSharedPointer<HTTPClient> httpClient;
    ServerStatus _serverStatus = ServerStatus::Free;

    bool canRunRequest() const;
    virtual void parse(const ServerResponse& response) = 0;

signals:
    void serverConfigChanged();

    void serverStatusChanged(const ServerStatus& status);
    void serverResponse(const ServerResponse& response);

    void serverRequestError(ResponseType responseType);
    void serverRequestSuccess(ResponseType responseType);
    void serverGlobalError(ServerGlobalErrorType globalErrorType);

    void newUserEntered(const UserObject&);

    void userNotFound();
    void userAlreadyExists();
    void userAlreadyConfirmed();

    void userStartedGame();
    void userUpdatedGame();
    void userFinishedGame();

    void serverLogged(const QString& log);//for QML

protected slots:
    virtual void httpRequestSuccessHandler(const QString& data);
    virtual void httpRequestFailedHandler(const QString& data);
};

typedef ServerComponent::ServerResponse ServerResponse;
typedef ServerComponent::ServerStatus ServerStatus;
typedef ServerComponent::ServerGlobalErrorType ServerGlobalErrorType;
typedef ServerComponent::ResponseType ResponseType;

#endif // SERVERCOMPONENT_H
