import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../components"
import "../tests"

Window
{
    title: "Control Window";
    x: 0;
    y: 0;
    width: 1500;
    height: 1000;
    visible: true;
    flags: Qt.Window;

    property int marginLeft: 50;
    property int marginTop: 10;
    property int columnShift: 400;

    ServerRemoteTest
    {
        id: testScreen;
        x: marginLeft;
        y: marginTop;
    }

    StandData
    {
        x: marginLeft + 700;
        y: marginTop;
    }

    GameSession
    {
        x: marginLeft + 700;
        y: marginTop + 260;
    }

    ServerData
    {
        id: serverComp;
        x: marginLeft + 700;
        y: marginTop + 360;
    }

    AppState
    {
        x: marginLeft + 700;
        y: marginTop + 460;
    }

    MindwaveComponent
    {
        id: mindWaveComp;
        x: marginLeft + 700;
        y: marginTop + 560;
    }

    Button
    {
        text: "Make Me Crash";
        visible: true;
        x: marginLeft + 1200;
        y: marginTop;
        onClicked: appController.testCrash();
    }   


    ACR122Card
    {
        id: arduinoComp;
        x: marginLeft + 300;
        y: marginTop + 280;
    }

    //    UserRegistrationData
    //    {

    //    }

    //    HealthCheckerComponent
    //    {
    //        x:marginLeft + 300;
    //        y:marginTop + 700;
    //        id:health
    //    }

}
