import QtQuick 2.0
import QtQuick.Controls 2.1
import com.app 1.0

Item
{
    property var lastStatus: ServerStatus.None;
    property int minimumShowTime: 1000;

    anchors.fill: parent;

    Component.onCompleted:
    {
        visible = false;
    }

    Connections
    {
        target:server;

        onServerStatusChanged:
        {
            lastStatus = status;

            if(ServerStatus.Busy)
            {
                preloderTimer.start();
                visible = true;
            }
        }
    }

    Rectangle
    {
        anchors.fill: parent;
        opacity: 0.0;
        color: "#1c1c1c";
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0.0;
    }

    BusyIndicator
    {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.topMargin: 50;
        anchors.leftMargin: 50;
        running: true;
        implicitHeight: 100;
        implicitWidth: 100;
    }

    Timer
    {
        id:preloderTimer;
        interval: minimumShowTime;
        running: false;
        repeat: false
        onTriggered:
        {
            if(lastStatus != ServerStatus.Busy)
            {
                preloderTimer.stop();
                visible = false;
            }
            else
            {
                preloderTimer.start();
                visible = true;
            }
        }
    }
}

