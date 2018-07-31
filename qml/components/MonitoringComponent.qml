import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

Item
{
    anchors.fill: parent;

    Text
    {
        x: 50;
        y: 50;
        id:versionText;
        Layout.alignment: Qt.AlignHCenter;
        text: "Version: " + standData.mainConfig.version;
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#888888";
    }

    Text
    {
        x: 50;
        y: 80;
        id:memoryText;
        Layout.alignment: Qt.AlignHCenter;
        text: "Memory: " + monitoring.memory + " MB";
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#888888";
    }
}
