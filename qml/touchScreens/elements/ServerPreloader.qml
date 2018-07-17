import QtQuick 2.0
import QtQuick.Controls 2.1
import com.app 1.0

Item
{
    anchors.fill: parent;

    Component.onCompleted:
    {
        visible = false;
    }

    Connections
    {
        target:server
        onServerStatusChanged:
        {
            visible = (status === ServerStatus.Busy);
        }
    }

    Rectangle
    {
        anchors.fill: parent;
        opacity: 0.9;
        color: "#1c1c1c";
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0.0;
    }

    BusyIndicator
    {
        anchors.centerIn: parent;
        running: true;
        implicitHeight: 200;
        implicitWidth: 200;
    }
}

