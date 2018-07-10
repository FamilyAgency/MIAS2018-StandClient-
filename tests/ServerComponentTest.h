#ifndef SERVERCOMPONENTTEST_H
#define SERVERCOMPONENTTEST_H

#include <QObject>
#include "components/ServerComponent.h"
#include "core/game/VelocityCalculator.h"
#include "core/game/GameProgress.h"

class ServerComponentTest: public ServerComponent
{
    Q_OBJECT

public:
    explicit ServerComponentTest(QObject *parent = nullptr);
    Q_INVOKABLE void fetchUserWithGameId(int rfid, int gameId);
    Q_INVOKABLE virtual void logout() override;
    Q_INVOKABLE void fetchDoesntExistUser(int rfid);
    Q_INVOKABLE void fetchPlayedRecentUser(int rfid);
    Q_INVOKABLE void fetchAlreadyPlayingUser(int rfid);

    Q_INVOKABLE void simulateServerTimeout();
    Q_INVOKABLE void simulateServerError();
    Q_INVOKABLE void finishedWithPrizes(int rfid);

private:
    int lastRfid = 1;
    int lastGameId = 1;

    QVector<QPointF> createPath(int pathId);
    VelocityCalculator createDifficult(int diff);
    QJsonArray createPathJsonArray(const QVector<QPointF>& path);
    QJsonObject createDiffJsonObject(const VelocityCalculator& velCalc);


private slots:
    void onFetchUser();
    void onFetchDoesntExistUser();
    void onFetchPlayedRecentUser();
    void onFetchAlreadyPlayingUser();
    void onUserLogout();

    void onSimulateServerError();
    void onSimulateServerTimeout();
    void onFinishedWithPrizes();
};

#endif // SERVERCOMPONENTTEST_H
