import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Controls 2.1
import com.app 1.0

Item
{
    id:error;
    anchors.fill: parent;

    Component.onCompleted:
    {
        visible = false;
    }

    Connections
    {
        target: server;

        onServerRequestError:
        {
            console.log("server error");
            visible = true;
        }

        onServerGlobalError:
        {
            console.log("server error");
            visible = true;
        }
    }

    Rectangle
    {
        anchors.fill: parent;
        opacity: 0.7;
        color: "red";
    }

    Button
    {
        anchors.fill: parent;
        opacity: 0.0;
    }

    Button
    {
        anchors.centerIn: parent;
        opacity: 1.0;
        text: "OK. Close Error";
        onClicked:
        {
            server.freeServer();
            error.visible = false;
        }
    }
}
