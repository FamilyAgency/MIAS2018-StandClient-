import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item
{
    id: backbtn;
    anchors.fill:  parent;

    Text
    {
        x: 20;
        y: 20;
        id:versionText;
        Layout.alignment: Qt.AlignHCenter;
        text: "Build: " + standData.buildNumber;
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#888888";
        visible: buildShow1.pressed;// && buildShow2.pressed;
    }

    Button
    {
        id: buildShow1;
        opacity: .0;
        visible: true;
        width: 100;
        height: 100;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left;
    }

    Button
    {
        id: buildShow2;
        opacity: .0;
        visible: true;
        width: 100;
        height: 100;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
    }
}
