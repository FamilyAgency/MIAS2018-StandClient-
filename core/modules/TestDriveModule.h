#ifndef TESTDRIVEMODULE_H
#define TESTDRIVEMODULE_H

#include <QObject>

class TestDriveModule : public QObject
{
    Q_OBJECT
public:
    explicit TestDriveModule(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TESTDRIVEMODULE_H