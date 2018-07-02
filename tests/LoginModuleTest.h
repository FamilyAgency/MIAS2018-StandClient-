#ifndef LOGINMODULETEST_H
#define LOGINMODULETEST_H

#include <QObject>
#include "core/LoginModule.h"
#include "tests/LoginModuleTest.h"
#include "core/game/VelocityCalculator.h"

class LoginModuleTest : public LoginModule
{
    Q_OBJECT
public:
    LoginModuleTest();
    virtual void setQmlContext(QQmlContext* qmlContext) override;

    Q_INVOKABLE virtual void loginSuccessTest(int gameId);
    Q_INVOKABLE virtual void logoutTest();
    Q_INVOKABLE void finished(int prizesCount);
    Q_INVOKABLE void userDoesntExist();
    Q_INVOKABLE void moduleError();
    Q_INVOKABLE void youArePlaying();
    Q_INVOKABLE void playedRecently();

private:
    QVector<QPointF> createPath(int pathId);
    VelocityCalculator createDifficult(int diff);

     GameProgress* createGamesOnStage1();
     GameProgress* createGamesOnStage2();
     GameProgress* createGamesOnStage3();

signals:

public slots:
};

#endif // LOGINMODULETEST_H
