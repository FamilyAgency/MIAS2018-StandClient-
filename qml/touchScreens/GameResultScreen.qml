import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import "../tools"
import "gameresult"

Item
{
    id: gameResultScreen;
    anchors.fill: parent;

    signal animComplete();
    signal animStart();

    property string mainTitleDefault: "Поздравляем!<br/>тебя ждет второй этап!<br/>Теперь ты знаешь <br/>все о Santa Fe <br/>и можешь управлять <br/>силой своих мыслей.";
    property string buttonTakeColaText: "ЗАБРАТЬ<br/>НАПИТОК";
    property string buttonSuperGameText: "ИГРАТЬ<br/>В СУПЕРИГРУ";

    signal startSuperGame();
    signal getColaCan();

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }

    Text
    {
        id: mainText;
       // anchors.top: parent.top;
       // anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 80 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

//    Button
//    {
//        id: colaBtn;

//        anchors.bottom: parent.bottom;
//        anchors.left: parent.left;

//        contentItem: Text
//        {
//            text: buttonTakeColaText;
//            font.family: "Helvetica";
//            font.pixelSize: 25;
//            color: "#ffffff";
//            horizontalAlignment: Text.AlignHCenter;
//            verticalAlignment: Text.AlignVCenter;
//        }

//        background: Rectangle
//        {
//            implicitHeight: 200;
//            implicitWidth: gameResultScreen.width * 0.5;
//            color: colaBtn.down ? "#3c2755" : "#801bfc";
//        }

//        onClicked:
//        {
//            confirmExitPopup.show();
//        }
//    }

//    Button
//    {
//        id: superBtn;

//        anchors.bottom: parent.bottom;
//        anchors.right: parent.right;

//        contentItem: Text
//        {
//            text: buttonSuperGameText;
//            font.family: "Helvetica";
//            font.pixelSize: 25;
//            color: "#ffffff";
//            horizontalAlignment: Text.AlignHCenter;
//            verticalAlignment: Text.AlignVCenter;

//        }

//        background: Rectangle
//        {
//            implicitHeight: 200;
//            implicitWidth: gameResultScreen.width * 0.5;
//            color: superBtn.down ? "#3c2755" : "#4e1a8a";
//        }

//        onClicked:
//        {
//            gameResultModule.superGameAcceptedButtonClick();
//        }
//    }

    ConfirmExitPopup
    {
        id:confirmExitPopup;

        onReject:
        {
            confirmExitPopup.hide();
             gameResultModule.superGameRejectedButtonClick();
        }

        onConfirm:
        {
            confirmExitPopup.hide();
             gameResultModule.superGameAcceptedButtonClick();
        }
    }


    function start()
    {
        visible = true;
        gameResultScreen.animComplete();
    }

    function stop()
    {
        visible = false;
        confirmExitPopup.hide();
    }
}
