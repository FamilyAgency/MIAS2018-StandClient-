import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

import com.app 1.0

Item
{
    anchors.fill: parent;
    anchors.centerIn: parent;

    Button
    {
        id:toggleVis;
        implicitWidth: 200;
        text:  locs.visible ? "Hide" : "Show";

        background: Rectangle
        {
            implicitWidth: 200;
            color: "#ffffff";
        }

        onClicked:
        {
            locs.visible = !locs.visible;
        }

    }

    ColumnLayout
    {
        id:locs;

        spacing: 10;
        visible: false;

        anchors.top:toggleVis.bottom;
        anchors.topMargin: 20;

        Button
        {
            text: "Intro";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.Intro);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "Instruction";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.Instruction);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "Roulette";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.Roulette);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "Game";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.Game);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "GameResult";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.GameResult);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "SuperGame";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.SuperGame);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "SuperGameResult";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.SuperGameResult);
                locs.visible = false;
            }
        }

        Button
        {
            implicitWidth: 200;
            text: "TestDrive";

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }

            onClicked:
            {
                appController.setAppStateTest(AppState.TestDrive);
                locs.visible = false;
            }
        }
    }
}
