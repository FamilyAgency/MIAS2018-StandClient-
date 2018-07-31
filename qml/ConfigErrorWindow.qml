import QtQuick 2.1
import QtQuick.Controls 2.2

ApplicationWindow
{
    title: qsTr("ConfigError");
    x: 420;
    y: 100;
    width: 500;
    height: 500;
    visible: true;
    id: core;

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
