import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import ".."
import "../touchScreens/game"
import com.app 1.0

Window
{
    objectName: "mainGameWindow";
    title: "Main Game Window";
    visible: true;
    id: mainGameWindow;
    flags: standData.mainConfig.gameScreenIsSplash ? Qt.SplashScreen : Qt.Window;
    width: standData.mainConfig.gameScreen.width;
    height: standData.mainConfig.gameScreen.height;
    x: standData.mainConfig.gameScreen.x;
    y: standData.mainConfig.gameScreen.y;

   // color: "#000000"

//    AdvantageDescription
//    {
//        id:a;
//    }

//    Component.onCompleted:
//    {
//       // a.setTexts("Довезёт и до города Санта-Фе,<br/>и до Санта Клауса!", "Сила мысли – это хорошо! А 200-сильный<br/>двигатель с 8-ступенчатой АКПП – лучше.<br/>8-ступенчатая коробка-автомат – это восемь<br/>степеней свободы на любой дороге.<br/>А в качестве приятного бонуса к комфортному<br/>вождению – экономия топлива!")
//       // a.setTexts("Полный привод –<br/>едем с умом!", "Система HTRAC анализирует, по какой дороге<br/>едет автомобиль, и автоматически распределяет<br/>нагрузку между осями. Она помогает проходить<br/>повороты безопаснее, и ехать по городу<br/>и бездорожью одинаково легко.");
//       // a.setTexts("Нет безвыходных ситуаций.<br/>Есть безопасный выход!", "Если сзади приближается другой автомобиль,<br/>система безопасного выхода предупредит<br/>об опасности и не даст разблокировать задние<br/>двери, чтобы пассажиры остались в салоне.");
//       // a.show();
//    }

    Connections
    {
        target:appController;
        onAppStateChanged:
        {
            setState(appState);
        }
    }

    MouseArea
    {
        anchors.fill: parent;
        onClicked:
        {
            focusedId.forceActiveFocus();
        }
    }

    Item
    {
        id:focusedId;
        focus: true;
        anchors.fill: parent;

        Keys.onPressed:
        {
            if (event.key === Qt.Key_Escape)
            {
                Qt.quit();
            }
        }
    }

    GameScreen
    {
        id: mainGameScreen;
    }

    SuperGameWinScreen
    {
        id: supergameWin;
    }

    function setState(appState)
    {
        supergameWin.hide();

        switch(appState)
        {
        case AppState.Intro:
        case AppState.Instruction:
        case AppState.Roulette:
            mainGameScreen.gameStop();
            break;

        case AppState.Game:
            mainGameScreen.gameStart()
            break;

            // case AppState.GameResult:
        case AppState.SuperGame:
            mainGameScreen.gameStop();
            break;

        case AppState.TestDrive:
            mainGameScreen.gameStop();
            break;

        case AppState.SuperGameResult:
            supergameWin.show();
            mainGameScreen.gameStop();
            break;
        }
    }

}
