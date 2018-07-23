import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import ".."
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


    Connections
    {
        target:appController;
        onAppStateChanged:
        {
            setState(appState);
        }
    }

    GameScreen
    {
        id:mainGameScreen;
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

    function setState(appState)
    {
        switch(appState)
        {
        case AppState.Intro:
            mainGameScreen.gameStop();
            break;

        case AppState.Instruction:
            mainGameScreen.gameStop();
            break;

        case AppState.Roulette:
            break;

        case AppState.Game:
            mainGameScreen.gameStart()
            break;

        case AppState.Result:
            mainGameScreen.gameStop();
            break;
        }
    }
}
