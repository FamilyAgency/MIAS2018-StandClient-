#ifndef SERVERREMOTECOMPONENT_H
#define SERVERREMOTECOMPONENT_H

#include <QObject>
#include <QJsonObject>
#include "components/ServerComponent.h"
#include "core/data/UserData.h"

class ServerRemoteComponent : public ServerComponent
{
    Q_OBJECT
    Q_PROPERTY(BaseUserInfo baseUserInfo READ baseUserInfo WRITE setBaseUserInfo NOTIFY baseUserInfoChanged)

public:
    explicit ServerRemoteComponent(QObject *parent = nullptr);

    Q_INVOKABLE void configRequest(int deviceId);
    Q_INVOKABLE void updatesRequest(int deviceId);

    Q_INVOKABLE void healthLogRequest(int deviceId);
    Q_INVOKABLE void allUsersRequest();
    Q_INVOKABLE void createUserRequest(bool isTestUser);
    Q_INVOKABLE void createUserRequest(const QString& name,
                                       const QString& surname,
                                       const QString& email,
                                       const QString& phone,
                                       bool test);

    Q_INVOKABLE void searchUserRequest(const QString& email, const QString& phone);
    Q_INVOKABLE void searchUserByIdRequest(int userId);
    Q_INVOKABLE void deleteAllTestUsersRequest();
    Q_INVOKABLE void verifyUserRequest(int userId);
    Q_INVOKABLE void confirmUserRequest(int userId, int code);
    Q_INVOKABLE void confirmPrizeRequest(int userId, int prizeid);

    virtual void parse(const ServerResponse& response) override;

    Q_INVOKABLE void clearBaseUserInfo();

    void setBaseUserInfo(const BaseUserInfo& baseUserInfo);
    BaseUserInfo baseUserInfo() const;

    //test
    Q_INVOKABLE void simulateServerError();

private:
    BaseUserInfo _baseUserInfo;
    void createBaseUserInfo(const QJsonObject& object);
    void handleRequestError(const ServerResponse&  response);



signals:
    void baseUserInfoChanged();
};

#endif // SERVERREMOTECOMPONENT_H
