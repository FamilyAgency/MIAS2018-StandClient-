#ifndef SERVERREMOTECOMPONENT_H
#define SERVERREMOTECOMPONENT_H

#include <QObject>
#include "components/ServerComponent.h"

class ServerRemoteComponent : public ServerComponent
{
    Q_OBJECT
public:
    explicit ServerRemoteComponent(QObject *parent = nullptr);

    Q_INVOKABLE void configRequest(int deviceId);
    Q_INVOKABLE void updatesRequest(int deviceId);

    Q_INVOKABLE void healthLogRequest(int deviceId);
    Q_INVOKABLE void allUsersRequest();
    Q_INVOKABLE void createUserRequest(bool isTestUser);
    Q_INVOKABLE void searchUserRequest(const QString& email, const QString& phone);
    Q_INVOKABLE void deleteAllTestUsersRequest();
    Q_INVOKABLE void verifyUserRequest(int id);
    Q_INVOKABLE void confirmUserRequest(int id, int code);

    virtual void parse(const ServerResponse& response) override;
};

#endif // SERVERREMOTECOMPONENT_H
