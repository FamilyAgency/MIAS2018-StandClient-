import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import ".."
import com.app 1.0


Window {
    objectName: "wnd2"
    visible: true
    id: mainGameWindow
    title: "Splash Window"
    flags: Qt.SplashScreen
    x: 2820
    width: 1920
    height: 1080

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
        id:mainGameScreen
    }

    function setState(appState)
    {
        mainGameScreen.gameStop();
        switch(appState)
        {
        case AppState.Login:

            break;

        case AppState.Instruction:

            break;

        case AppState.Game:
            mainGameScreen.gameStart()
            break;

        case AppState.Result:

            break;
        }
    }
}
