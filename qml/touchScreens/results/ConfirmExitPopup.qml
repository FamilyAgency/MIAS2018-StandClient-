import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: popup;
    property string mainTitleDefault: "УВЕРЕН,<br/>ЧТО НЕ ХОЧЕШЬ<br/>СЫГРАТЬ В СУПЕР-ИГРУ<br/>И ПОЛУЧИТЬ<br/>АВТОМОБИЛЬ SANTA FE";
    property string buttonTakeColaText: "ЗАБРАТЬ<br/>НАПИТОК";
    property string buttonSuperGameText: "ИГРАТЬ<br/>В СУПЕРИГРУ";

    signal reject();
    signal confirm();

    visible:false;
    anchors.fill: parent;
    anchors.centerIn: parent;

    Rectangle
    {
        anchors.fill: parent;
        color: "#1c1c1c";
    }


    Text
    {
        id:mainText;
        anchors.verticalCenterOffset: -200;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 50;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Button
    {
        id: colaBtn;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: 200;
        anchors.left: parent.left;

        contentItem: Text
        {
            text: buttonTakeColaText;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            implicitHeight: 200;
            implicitWidth: result.width * 0.5;
            color: colaBtn.down ? "#3c2755" : "#801bfc";
        }

        onClicked:
        {
            popup.reject();
        }
    }

    Button
    {
        id: superBtn;

        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: 200;
        anchors.right: parent.right;

        contentItem: Text
        {
            text: buttonSuperGameText;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;

        }

        background: Rectangle
        {
            implicitHeight: 200;
            implicitWidth: result.width * 0.5;
            color: superBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            popup.confirm();
        }
    }

    function show()
    {
        visible = true;
    }

    function hide()
    {
        visible = false;
    }
}
