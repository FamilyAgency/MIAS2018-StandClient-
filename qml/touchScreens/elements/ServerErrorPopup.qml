import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import com.app 1.0

Item
{
    id: error;
    anchors.fill: parent;

    Rectangle
    {
        anchors.fill: parent;
        opacity: 0.7;
        color: "red";
    }

    Text
    {
        id: mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "Обратитесь за помощью к промоутеру<br/>Игра не может быть продолжена";
        font.family: "Helvetica";
        font.pixelSize: 25;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
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
            appController.backToIntro();
            server.freeServer();
            error.visible = false;
        }
    }

    Component.onCompleted:
    {
        visible = false;
    }

    Connections
    {
        target: server;

        onServerRequestError:
        {
           // cantPlayHandler("Что-то пошло не так!<br/>Обратитесь к промоутеру.");
            console.log("server error");
            visible = true;
        }

        onServerGlobalError:
        {
            console.log("server error");
            visible = true;
        }
    }
}
