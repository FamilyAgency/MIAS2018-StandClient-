import QtQuick 2.0
import "../components"
import "../tests"
import QtQuick.Window 2.2

Item
{
    property int marginLeft: 50;
    property int marginTop: 10;
    property int columnShift: 400;

    StandData
    {
        x: marginLeft;
        y: marginTop;
    }

    GameSession
    {
        x: marginLeft;
        y: marginTop + 480;
    }

    AppState
    {
        x: marginLeft;
        y: marginTop + 620;
    }

    MindwaveComponent
    {
        id: mindWaveComp;
        x: marginLeft + 300;
        y: marginTop;
    }

    ACR122Card
    {
        id: arduinoComp;
        x: marginLeft + 300;
        y: marginTop + 280;
    }

    ServerComponent
    {
        id: serverComp;
        x: marginLeft;
        y: marginTop + 720;
    }

//    HealthCheckerComponent
//    {
//        x:marginLeft + 300;
//        y:marginTop + 700;
//        id:health
//    }

    TestScreen
    {
        id: testScreen;
        x: marginLeft + 800;
        y: marginTop;
    }

//    UserRegistrationData
//    {

//    }
}
