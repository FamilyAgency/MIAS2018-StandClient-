import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../../components"
import "../../touchScreens/elements"
import "../../touchScreens"
import com.app 1.0

Item
{
    anchors.fill: parent;

    IntroScreenTest
    {
        id: introScreenTest;
    }

    Component.onCompleted:
    {
        setState(appController.getAppState());
    }

    Connections
    {
        target:appController;

        onAppStateChanged:
        {
            setState(appState);
        }
    }

    function setState(appState)
    {
        hideAll();

        switch(appState)
        {
        case AppState.Intro:
            introScreenTest.visible = true;
            break;

        case AppState.Instruction:

            break;

        case AppState.Roulette:

            break;

        case AppState.Game:

            break;

        case AppState.GameResult:

            break;

        case AppState.SuperGame:

            break;

        case AppState.SuperGameResult:
            break;
        }
    }

    function hideAll()
    {
        introScreenTest.visible = false;
    }
}
