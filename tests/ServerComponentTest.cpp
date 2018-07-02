#include "ServerComponentTest.h"

ServerComponentTest::ServerComponentTest(QObject *parent) : ServerComponent(parent)
{
    name = "Server Test";
}

void ServerComponentTest::fetchUser(int deviceId, int rfid)
{
    ServerResponse response;
    response.type = ResponseType::UserFetched;
    response.body = "json";
    emit serverResponse(response);
}

