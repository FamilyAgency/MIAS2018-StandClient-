import QtQuick 2.1
import QtQuick.Controls 2.2
import "tests/touchScreens"
import "mainScreens"
import "controlScreens"
import com.app 1.0

ApplicationWindow
{
    visible: true;
    width: 500;
    height: 500;
    x: 420;
    y: 100;
    title: qsTr("ConfigError");
    id: core;

    Component.onCompleted:
    {

    }

    Text
    {        
        id:promtText;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: configController.getErrorMessage();
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#990000";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }
}
