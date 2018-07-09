#include "RFIDComponentTest.h"

RFIDComponentTest::RFIDComponentTest(QObject *parent) : RFIDComponent(parent)
{

}

void RFIDComponentTest::testDataCome(int id)
{
    emit onRFIDRecieve(id);
}
