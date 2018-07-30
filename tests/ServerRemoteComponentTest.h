#ifndef SERVERREMOTECOMPONENTTEST_H
#define SERVERREMOTECOMPONENTTEST_H

#include <QObject>
#include "components/server/ServerRemoteComponent.h"

class ServerRemoteComponentTest : public ServerRemoteComponent
{
    Q_OBJECT
public:
    explicit ServerRemoteComponentTest(QObject *parent = nullptr);

    Q_INVOKABLE void simulateServerError();
    Q_INVOKABLE void simulateServerTimeout();
};

#endif // SERVERREMOTECOMPONENTTEST_H
