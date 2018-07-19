import QtQuick 2.0
import "../components"
import "../tests"
import QtQuick.Window 2.2

Item
{
    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;

    StandData
    {
        x:marginLeft;
        y:marginTop;
    }

    GameSession
    {
        x:marginLeft;
        y:marginTop + 480;
    }

    AppState
    {
        x:marginLeft;
        y:marginTop + 620;
    }

    MindwaveComponent
    {
        x:marginLeft + 300;
        y:marginTop;
        id:mindWaveComp;
    }

    RFIDComponent
    {
        x:marginLeft + 300;
        y:marginTop + 280;
        id:arduinoComp;
    }

    ServerComponent
    {
        x:marginLeft + 300;
        y:marginTop + 480;
        id:serverComp;
    }

    HealthCheckerComponent
    {
        x:marginLeft + 300;
        y:marginTop + 600;
        id:health
    }

    TestScreen
    {
        x:marginLeft + 800;
        y:marginTop;
        id:testScreen;
    }

    UserRegistrationData
    {

    }
}
