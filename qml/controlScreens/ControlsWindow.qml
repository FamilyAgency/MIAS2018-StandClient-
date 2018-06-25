import QtQuick 2.0
import "../components"
import "../tests"

Item {
    property int marginLeft:50;
    property int marginTop:10;
    property int columnShift:400;   

    function setState(state)
    {

    }

    StandData
    {
        x:marginLeft;
        y:marginTop;
    }

    UserData
    {
        x:marginLeft;
        y:marginTop + 100;
    }


    GameSession
    {
        x:marginLeft;
        y:marginTop + 350;
    }

    AppState
    {
        x:marginLeft;
        y:marginTop + 500;
    }

    MindwaveComponent
    {
        x:marginLeft + 300;
        y:marginTop;
        id:mindWave;
    }

    ArduinoComponent
    {
        x:marginLeft + 300;
        y:marginTop + 250;
        id:arduino;
    }

    MainServer
    {
        x:marginLeft + 300;
        y:marginTop + 450;
        id:server;
    }

    HealthCheckerComponent
    {
        x:marginLeft + 300;
        y:marginTop + 600;
        id:health
    }

    Logger
    {
        x:marginLeft + 800;
        y:marginTop;
        id:logger;
    }

    TestScreen
    {
        x:marginLeft + 800;
        y:marginTop + 300;
        id:testScreen;
    }
}
