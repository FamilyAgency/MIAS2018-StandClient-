#ifndef SERVERCOMPONENTTEST_H
#define SERVERCOMPONENTTEST_H

#include <QObject>
#include "components/ServerComponent.h"

class ServerComponentTest: public ServerComponent
{
    Q_OBJECT

public:
    explicit ServerComponentTest(QObject *parent = nullptr);
    Q_INVOKABLE virtual void fetchUser(int rfid) override;
    Q_INVOKABLE void fetchDoesntExistUser(int rfid);
    Q_INVOKABLE void fetchPlayedRecentUser(int rfid);
    Q_INVOKABLE void fetchAlreadyPlayingUser(int rfid);

    Q_INVOKABLE void simulateServerTimeout();
    Q_INVOKABLE void simulateServerError();
    Q_INVOKABLE void finishedWithPrizes(int rfid);

private:
    int lastRfid = 1;

private slots:
    void onFetchUser();
    void onFetchDoesntExistUser();
    void onFetchPlayedRecentUser();
    void onFetchAlreadyPlayingUser();

    void onSimulateServerError();
    void onSimulateServerTimeout();
    void onFinishedWithPrizes();
};

#endif // SERVERCOMPONENTTEST_H
