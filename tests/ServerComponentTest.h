#ifndef SERVERCOMPONENTTEST_H
#define SERVERCOMPONENTTEST_H

#include <QObject>
#include "components/ServerComponent.h"

class ServerComponentTest: public ServerComponent
{
    Q_OBJECT

public:
    explicit ServerComponentTest(QObject *parent = nullptr);
    virtual void fetchUser(int deviceId, int rfid) override;
};

#endif // SERVERCOMPONENTTEST_H
