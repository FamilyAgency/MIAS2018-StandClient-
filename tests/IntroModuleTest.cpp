#include "IntroModuleTest.h"

IntroModuleTest::IntroModuleTest():IntroModule()
{

}

void IntroModuleTest::setQmlContext(QQmlContext* qmlContext)
{
    IntroModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("loginModule", this);
}

void IntroModuleTest::loginSuccessTest(int gameId)
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

    GameProgress* gameProgress = createGamesOnStage1();

    if(gameId == 2)
    {
        gameProgress = createGamesOnStage2();
    }
    else if(gameId == 3)
    {
        gameProgress = createGamesOnStage3();
    }

    userData->setGameProgess(gameProgress);
    setUserState(UserState::CanPlay);
    setState(LoginState::Login);
}

GameProgress* IntroModuleTest::createGamesOnStage1()
{
    userData->setName("Александр");
    userData->setSurname("Александров");
    userData->setId(665);

    GameProgress* gameProgress = userData->getGameProgess();
    gameProgress->setCurrentGameId(1);
    gameProgress->setCleanTime(0.0f);

    QVector<OneGameData> gamesData;

    OneGameData gameData1;
    gameData1.setPath(createPath(1));
    gameData1.setDescription("test task");
    gameData1.setDifficult(createDifficult(3));
    gameData1.setComplete(false);
    gameData1.setTime(10.5f);
    gameData1.setId(1);

    OneGameData gameData2;
    gameData2.setPath(createPath(2));
    gameData2.setDescription("test task");
    gameData2.setDifficult(createDifficult(4));
    gameData2.setComplete(false);
    gameData2.setTime(20.5f);
    gameData2.setId(2);

    OneGameData gameData3;
    gameData3.setPath(createPath(3));
    gameData3.setDescription("test task");
    gameData3.setDifficult(createDifficult(5));
    gameData3.setComplete(false);
    gameData3.setTime(0.0f);
    gameData3.setId(3);

    gamesData.push_back(gameData1);
    gamesData.push_back(gameData2);
    gamesData.push_back(gameData3);
    gameProgress->setGames(gamesData);

    return gameProgress;
}

GameProgress* IntroModuleTest::createGamesOnStage2()
{
    userData->setName("Константин");
    userData->setSurname("Константинов");
    userData->setId(165);

    GameProgress* gameProgress = userData->getGameProgess();
    gameProgress->setCurrentGameId(2);
    gameProgress->setCleanTime(0.0f);

    QVector<OneGameData> gamesData;

    OneGameData gameData1;
    gameData1.setPath(createPath(1));
    gameData1.setDescription("test task");
    gameData1.setDifficult(createDifficult(3));
    gameData1.setComplete(true);
    gameData1.setTime(10.5f);
    gameData1.setId(1);

    OneGameData gameData2;
    gameData2.setPath(createPath(2));
    gameData2.setDescription("test task");
    gameData2.setDifficult(createDifficult(4));
    gameData2.setComplete(false);
    gameData2.setTime(20.5f);
    gameData2.setId(2);

    OneGameData gameData3;
    gameData3.setPath(createPath(3));
    gameData3.setDescription("test task");
    gameData3.setDifficult(createDifficult(5));
    gameData3.setComplete(false);
    gameData3.setTime(0.0f);
    gameData3.setId(3);

    gamesData.push_back(gameData1);
    gamesData.push_back(gameData2);
    gamesData.push_back(gameData3);
    gameProgress->setGames(gamesData);

    return gameProgress;

}

GameProgress* IntroModuleTest::createGamesOnStage3()
{
    userData->setName("Петр");
    userData->setSurname("Петрович");
    userData->setId(6665);

    GameProgress* gameProgress = userData->getGameProgess();
    gameProgress->setCurrentGameId(3);
    gameProgress->setCleanTime(0.0f);

    QVector<OneGameData> gamesData;

    OneGameData gameData1;
    gameData1.setPath(createPath(1));
    gameData1.setDescription("test task");
    gameData1.setDifficult(createDifficult(3));
    gameData1.setComplete(true);
    gameData1.setTime(10.5f);
    gameData1.setId(1);

    OneGameData gameData2;
    gameData2.setPath(createPath(2));
    gameData2.setDescription("test task");
    gameData2.setDifficult(createDifficult(4));
    gameData2.setComplete(true);
    gameData2.setTime(20.5f);
    gameData2.setId(2);

    OneGameData gameData3;
    gameData3.setPath(createPath(3));
    gameData3.setDescription("test task");
    gameData3.setDifficult(createDifficult(5));
    gameData3.setComplete(false);
    gameData3.setTime(0.0f);
    gameData3.setId(3);

    gamesData.push_back(gameData1);
    gamesData.push_back(gameData2);
    gamesData.push_back(gameData3);
    gameProgress->setGames(gamesData);

    return gameProgress;
}

void IntroModuleTest::finished(int prizesCount)
{
    userData->setName("Игорь");
    userData->setSurname("Завершалов");
    userData->setId(665);
    userData->setFirstTime(false);
    userData->setFinished(true);
    userData->setExist(true);
    userData->setWaitEnoughToPlay(true);

    QVariantList prizes;
    for(int i  = 0; i < prizesCount; i++)
    {
         prizes.append(true);
    }

    auto prizeDiff = userData->maxPrizesCount - prizes.length();
    if(prizeDiff < 0)
    {
        // server error
        qDebug()<< "To much prizes!!!!!!!!!!!!!!";
    }
    else if (prizeDiff > 0)
    {
        for(int i  = 0; i < prizeDiff; i++)
        {
             prizes.append(false);
        }
    }

    userData->setPrizes(prizes);
    setUserState(UserState::Finished);
    //setState(LoginState::Login);
}

void IntroModuleTest::moduleError()
{
    setState(LoginState::Error);
}

void IntroModuleTest::youArePlaying()
{
    userData->setName("Игорь");
    userData->setSurname("Хитрец");
    userData->setId(65);
    setUserState(UserState::YouArePlaying);
}

void IntroModuleTest::playedRecently()
{
    userData->setName("Игорь");
    userData->setSurname("Хитрец");
    userData->setId(65);
    userData->setFirstTime(false);
    userData->setFinished(true);
    userData->setExist(true);
    userData->setWaitEnoughToPlay(false);
    setUserState(UserState::WasRecently);
}

void IntroModuleTest::userDoesntExist()
{
    userData->setName("----");
    userData->setSurname("----");
    userData->setId(-1000000);
    userData->setFirstTime(false);
    userData->setFinished(false);
    userData->setExist(false);
    userData->setWaitEnoughToPlay(false);
    setUserState(UserState::DoesntExists);
}

void IntroModuleTest::logoutTest()
{
    userData->setName("");
    userData->setSurname("");
    userData->setId(-1);
    setUserState(UserState::None);
    setState(LoginState::Logout);
}

QVector<QPointF> IntroModuleTest::createPath(int pathId)
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

VelocityCalculator IntroModuleTest::createDifficult(int diff)
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

void IntroModuleTest::rfidRecieved(int id)
{
    onRFIDRecieve(id);
}


