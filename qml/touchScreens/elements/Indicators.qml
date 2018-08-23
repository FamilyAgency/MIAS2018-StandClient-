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
            visible: rfidIndicator.visible;

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
            visible: mindwaveIndicator.visible;

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
        // console.log("device state", state);
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
    }

    function setState(appState)
    {
//        rfidIndicator.visible = false;

//        switch(appState)
//        {
//        case AppState.Intro:
//            if(showMindwaveError() || showRfidError())
//            {
//                mindwaveIndicator.visible = true;
//                rfidIndicator.visible = true;
//            }
//            else
//            {
//                mindwaveIndicator.visible = false;
//                rfidIndicator.visible = false;
//            }
//            break;

//        case AppState.Instruction:
//        case AppState.Roulette:
//        case AppState.Game:
//        case AppState.GameResult:
//        case AppState.SuperGame:
//            showMindwaveError();
//            break;

//        case AppState.SuperGameResult:
//        case AppState.TestDrive:
//            mindwaveIndicator.visible = false;
//            break;
//        }
    }

    function showMindwaveError()
    {
        mindwaveIndicator.visible = mindwaveIndicator.color != goodColor;
        return mindwaveIndicator.visible;
    }

    function showRfidError()
    {
        rfidIndicator.visible = rfidIndicator.color != goodColor;
        return rfidIndicator.visible;
    }
}
