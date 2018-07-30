#include "ServerRemoteComponentTest.h"

ServerRemoteComponentTest::ServerRemoteComponentTest(QObject *parent) : ServerRemoteComponent(parent)
{

}

void ServerRemoteComponentTest::simulateServerError()
{
    QNetworkRequest request(QString("http://mias2018.familyagency.ru"));
    commonRequest(ResponseType::VerifyUserRequest, request, HTTPMethod::GET);
}

void ServerRemoteComponentTest::simulateServerTimeout()
{
    QNetworkRequest request(QString("http://familyagency.ru/lab/infloop.php"));
    commonRequest(ResponseType::VerifyUserRequest, request, HTTPMethod::GET);
}
