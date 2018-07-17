import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: result;
    property string mainTitleDefault: "ПОЗДРАВЛЯЕМ";
    property string buttonTakeColaText: "ЗАБРАТЬ<br/>НАПИТОК";
    property string buttonSuperGameText: "ИГРАТЬ<br/>В СУПЕРИГРУ";


    anchors.fill: parent;
    anchors.centerIn: parent;

    Text
    {
        id:mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Button
    {
        id: colaBtn;

        anchors.bottom: parent.bottom;
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
            confirmExitPopup.show();
        }
    }

    Button
    {
        id: superBtn;

        anchors.bottom: parent.bottom;
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

        }
    }

    ConfirmExitPopup
    {
        id:confirmExitPopup;

        onReject:
        {
            confirmExitPopup.hide();
        }

        onConfirm:
        {
            confirmExitPopup.hide();
        }

    }

    function stop()
    {
        confirmExitPopup.hide();
    }
}
