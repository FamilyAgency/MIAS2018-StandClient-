import QtQuick 2.0
import com.app 1.0

Item
{
    id: indicators;

    property int indSpacing: 10;
    property string badColor: "#990000";
    property string goodColor: "#009900";
    property string middleColor: "#999900";
    property int bgCircleSize: 36;
    property int circleSize: 22;

    anchors.fill: parent;

    Row
    {
        spacing: indSpacing;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.rightMargin: indSpacing;
        anchors.topMargin: indSpacing;

        Rectangle
        {
            id: rfidIndicatorBg;

            implicitHeight: bgCircleSize;
            implicitWidth: bgCircleSize;
            radius: bgCircleSize * 0.5;
            color: rfidIndicator.color;
            opacity: 0.6;

            Rectangle
            {
                id: rfidIndicator;

                anchors.verticalCenter: parent.verticalCenter;
                anchors.horizontalCenter: parent.horizontalCenter;

                implicitHeight: circleSize;
                implicitWidth: circleSize;
                radius: circleSize * 0.5;
                color: middleColor;
            }
        }

        Rectangle
        {
            id: mindwaveIndicatorBg;

            implicitHeight: bgCircleSize;
            implicitWidth: bgCircleSize;
            radius: bgCircleSize * 0.5;
            color: mindwaveIndicator.color;
            opacity: 0.6;

            Rectangle
            {
                id: mindwaveIndicator;

                anchors.verticalCenter: parent.verticalCenter;
                anchors.horizontalCenter: parent.horizontalCenter;

                implicitHeight: circleSize;
                implicitWidth: circleSize;
                radius: circleSize * 0.5;
                color: middleColor;
            }
        }
    }

    Connections
    {
        target: rfid;

        onCardReaderEnabled:
        {
            rfidIndicator.color = enabled ? goodColor : badColor;

            if(AppState.Intro === appController.getAppState())
            {
                //checkRFID();
               // show2IfOneBad();
            }
        }
    }

    Connections
    {
        target: mind;

        onDeviceStateChanged:
        {
            deviceStateChanged(state);
        }
    }

    Component.onCompleted:
    {
        deviceStateChanged(mind.getDeviceState());
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

    function deviceStateChanged(state)
    {
        switch(state)
        {
        case DeviceState.Scanning:
            mindwaveIndicator.color = middleColor;
            break;

        case DeviceState.NotScanning:
            mindwaveIndicator.color = badColor;
            break;

        case DeviceState.Reading:
            mindwaveIndicator.color = mind.isSignalLevelMax() ? goodColor : middleColor;
            break;

        case DeviceState.None:
            mindwaveIndicator.color = badColor;
            break;
        }

        var appState = appController.getAppState();
        if(AppState.SuperGameResult !== appState && AppState.TestDrive !== appState)
        {
            checkMind();
        }
    }

    function setState(appState)
    {
        rfidIndicator.visible = false;
        rfidIndicatorBg.visible = false;
        mindwaveIndicator.visible = false;
        mindwaveIndicatorBg.visible = false;

        switch(appState)
        {
        case AppState.Intro:
           // checkRFID();
            checkMind();
           // show2IfOneBad();
            break;

        case AppState.Instruction:
        case AppState.Roulette:
        case AppState.Game:
        case AppState.GameResult:
        case AppState.SuperGame:
            checkMind();
            break;

        case AppState.SuperGameResult:
        case AppState.TestDrive:
            break;
        }
    }

    function checkRFID()
    {
        rfidIndicator.visible =  (rfidIndicator.color == badColor);
        rfidIndicatorBg.visible =  (rfidIndicator.color == badColor);
    }

    function checkMind()
    {
        mindwaveIndicator.visible =  (mindwaveIndicator.color == badColor || mindwaveIndicator.color == middleColor);
        mindwaveIndicatorBg.visible =  (mindwaveIndicator.color == badColor || mindwaveIndicator.color == middleColor);
    }

    function show2IfOneBad()
    {
        if(mindwaveIndicator.visible)
        {
            rfidIndicator.visible = true;
            rfidIndicatorBg.visible = true;
        }
        else if( rfidIndicator.visible)
        {
            mindwaveIndicator.visible = true;
            mindwaveIndicatorBg.visible = true;
        }
    }
}
