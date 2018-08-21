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
        }
    }

    Connections
    {
        target: mind;

        onDeviceStateChanged:
        {
            deviceStateChanged(state);
        }

        onPoorSignalLevelChanged:
        {
            if(mind.poorSignalLevel == 100)
            {
               //  console.log("poorSignalLevel 100");
                mindwaveIndicator.color = goodColor;
            }
            else
            {
                 mindwaveIndicator.color = middleColor;
            }
        }
    }

    Component.onCompleted:
    {
         deviceStateChanged(mind.getDeviceState());
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
            break;

        case DeviceState.None:
            mindwaveIndicator.color = badColor;
            break;
        }
    }
}
