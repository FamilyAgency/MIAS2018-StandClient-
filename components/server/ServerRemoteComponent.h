#ifndef SERVERREMOTECOMPONENT_H
#define SERVERREMOTECOMPONENT_H

#include <QObject>
#include <QJsonObject>
#include "components/ServerComponent.h"
#include "core/data/UserData.h"
#include "core/data/DilerData.h"

class ServerRemoteComponent : public ServerComponent
{
    Q_OBJECT

public:
    explicit ServerRemoteComponent(QObject *parent = nullptr);

    Q_INVOKABLE void configRequest(int deviceId);
    Q_INVOKABLE void updatesRequest(int deviceId);

    Q_INVOKABLE void healthLogRequest(int deviceId);
    Q_INVOKABLE void allUsersRequest();
    Q_INVOKABLE void createUserRequest();
    Q_INVOKABLE void createUserRequest(const QString& name,
                                       const QString& surname,
                                       const QString& email,
                                       const QString& phone,
                                       const QString& gender = "M");

    Q_INVOKABLE void searchUserRequest(const QString& email, const QString& phone);

    Q_INVOKABLE void deleteAllTestUsersRequest();
    Q_INVOKABLE void verifyUserRequest(int userId);
    Q_INVOKABLE void confirmUserRequest(int userId, int code);
    Q_INVOKABLE void confirmPrizeRequest(int userId, int prizeid);

    Q_INVOKABLE virtual void searchUserByIdRequest(int userId) override;
    Q_INVOKABLE virtual void startGameRequest(int userId) override;
    Q_INVOKABLE virtual void updateGameRequest(int userId) override;
    Q_INVOKABLE virtual void finishGameRequest(int userId) override;   
    Q_INVOKABLE virtual void logout();

    Q_INVOKABLE virtual void getDealersRequest() override;
    Q_INVOKABLE virtual void testDriveRequest(int userId, int dealerId) override;

    virtual void start() override;
    virtual void stop() override;

    friend class ServerRemoteComponentTest;

protected:
    virtual void parse(const ServerResponse& response) override;

private:
    BaseUserData _baseUserData;
    PrizesUserData _prizesUserData;
    GameUserData _gameUserData;

    void setBaseUserData(const BaseUserData& value);
    BaseUserData baseUserData() const;

    void setPrizesUserData(const PrizesUserData& value);
    PrizesUserData prizesUserData() const;

    void setGameUserData(const GameUserData& value);
    GameUserData gameUserData() const;

    void commonRequest(ResponseType type, const QNetworkRequest& request, HTTPMethod httpMethod, const QByteArray& data = 0);

    void createBaseUserData(const QJsonObject& object);
    void createPrizesUserData(const QJsonObject& object);
    void createGameUserData(const QJsonObject& object);
    void handleRequestError(const ServerResponse&  response);

    void createDilersData(const QJsonArray& jsonArray);

signals:
     void baseUserDataRecived(const BaseUserData& baseUserData);
     void dilersDataUpdated(const QVariantList& dilersData);
};

#endif // SERVERREMOTECOMPONENT_H
