#ifndef RFIDCOMPONENTTEST_H
#define RFIDCOMPONENTTEST_H

#include <QObject>
#include "components/RFIDComponent.h"

class RFIDComponentTest : public RFIDComponent
{
    Q_OBJECT
public:
    explicit RFIDComponentTest(QObject *parent = nullptr);
    Q_INVOKABLE void testDataCome(int id);

};

#endif // RFIDCOMPONENTTEST_H
