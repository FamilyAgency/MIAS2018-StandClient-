#include "LoginModuleTest.h"

LoginModuleTest::LoginModuleTest():LoginModule()
{

}

void LoginModuleTest::setQmlContext(QQmlContext* qmlContext)
{
     qmlContext->setContextProperty("loginModule", this);
}

void LoginModuleTest::loginSuccessTest()
{
    userData->setName("Александр");
    userData->setSurname("Александров");
    userData->setId(665);

    userData->setFirstTime(true);
    userData->setFinished(false);
    userData->setExist(true);
    userData->setWaitEnoughToPlay(true);

    QVariantList prizes;
    prizes.append(true);
    prizes.append(false);
    userData->setPrizes(prizes);


    GameProgress* gameProgress = new GameProgress();
    gameProgress->setCurrentStage(1);

    QVector<OneGameData> gamesData;

    OneGameData gameData1;
    gameData1.setPath(createPath(1));
    gameData1.setDescription("test task");
    gameData1.setDifficult(createDifficult(3));
    gameData1.clearUserData();
    gamesData.push_back(gameData1);

    OneGameData gameData2;
    gameData2.setPath(createPath(2));
    gameData2.setDescription("test task");
    gameData2.setDifficult(createDifficult(4));
    gameData2.clearUserData();
    gamesData.push_back(gameData2);

    OneGameData gameData3;
    gameData3.setPath(createPath(3));
    gameData3.setDescription("test task");
    gameData3.setDifficult(createDifficult(5));
    gameData3.clearUserData();
    gamesData.push_back(gameData3);


    gameProgress->setGames(gamesData);
    userData->setGameProgess(gameProgress);
    setState(LoginState::Login);
}

void LoginModuleTest::logoutTest()
{
    userData->setName("");
    userData->setSurname("");
    userData->setId(-1);

    setState(LoginState::Logout);
}

QVector<QPointF> LoginModuleTest::createPath(int pathId)
{
    QVector<QPointF> path;
    QPointF point1 = QPointF(388, 88);
    QPointF point2 = QPointF(621, 71 );
    QPointF point3 = QPointF(970, 114);
    QPointF point4 = QPointF(223, 222);
    QPointF point5 = QPointF(347, 243);
    QPointF point6 = QPointF(467, 264);
    QPointF point7 = QPointF(690, 300);
    QPointF point8 = QPointF(987, 207);
    QPointF point9 = QPointF(218, 422);
    QPointF point10 = QPointF(511, 357);
    QPointF point11 = QPointF(969, 389);
    QPointF point12 = QPointF(1152, 379);
    QPointF point13 = QPointF(315, 537);
    QPointF point14 = QPointF(573, 417);
    QPointF point15 = QPointF(666, 500);
    QPointF point16 = QPointF(735, 458);
    QPointF point17 = QPointF(917, 495);
    QPointF point18 = QPointF(913, 570);
    QPointF point19 = QPointF(1144, 616);
    QPointF point20 = QPointF(1002, 316);

    //penta
    //path.clear();
    //path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
    //velocitycalculator.setLimits(0, 3.5, 40);
    //gameTasks.append(new GameTask(path, velocitycalculator));

    path.clear();

    switch(pathId)
    {
        case 1:
            path<<point4<<point6<<point10<<point7<<point16<<point17;
        break;

        case 2:
            path<<point17<<point20<<point3<<point2;
        break;

        case 3:
            path<<point2<<point1<<point6<<point5<<point9;
        break;

        case 4:
            path<<point9<<point13<<point10<<point14<<point15<<point16<<point17<<point18<<point19;
        break;

        case 5:
           path<<point19<<point12<<point11<<point20<<point8<<point10<<point1;
        break;
    }

    return path;
}

VelocityCalculator LoginModuleTest::createDifficult(int diff)
{
    VelocityCalculator velocitycalculator;
    switch(diff)
    {
        case 0:
           velocitycalculator.setLimits(2.0f, 2.5f, 30.0f);
        break;

        case 1:
           velocitycalculator.setLimits(2.0f, 3.5f, 40.0f);
        break;

        case 2:
            velocitycalculator.setLimits(2.0f, 3.3f, 45.0f);
        break;

        case 3:
           velocitycalculator.setLimits(2, 3, 60);
        break;

        case 4:
            velocitycalculator.setLimits(2, 2, 70);
        break;

        case 5:
           velocitycalculator.setLimits(2, 3, 75);
        break;
    }


    return velocitycalculator;
}


