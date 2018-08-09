import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "elements"
import "../tools"
import "gameresult"

Item
{
    id: gameResultScreen;
    anchors.fill: parent;

    signal animComplete();
    signal animStart();

    property string mainTitleDefault: "Поздравляем!<br/>тебя ждет второй этап!<br/>Теперь ты знаешь <br/>все о Santa Fe <br/>и можешь управлять <br/>силой своих мыслей.";
    property string mainTitleDefault2: "Сыграй в супер-игру<br/>и получи в подарок<br/>освежающий напиток";
    property string buttonTakeColaText: "НЕТ, СПАСИБО";
    property string buttonSuperGameText: "ХОЧУ<br/>СЫГРАТЬ";
    property real btnMarginBottom: 100 * consts.designScale;

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

        OpacityAnimator on opacity
        {
            id: opacityAnim;
            from: 1;
            to: 0;
            duration: 700;
            running: false;
            easing.type: "InOutCubic";
        }

        ScaleAnimator on scale
        {
            id: scaleAnim;
            from: 1;
            to: 0.5;
            duration: 700;
            running:false;
            easing.type: "InOutCubic";
        }
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

        onClicked:
        {
           // gameResultScreen.animStart();
           // rouletteModule.startRoll();
            gameResultModule.superGameAcceptedButtonClick();
            brb.hide();
        }
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonSuperGameText);
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

    Timer
    {
        id:hideIntroTimer;
        running: false;
        interval : 3000;
        onTriggered:
        {
            opacityAnim.from = 1;
            opacityAnim.to = 0;
            opacityAnim.start();
            scaleAnim.from = 1;
            scaleAnim.to = 0;
            scaleAnim.start();
            hideIntroTimer.stop();
            showIntro2Timer.start();
        }
    }

    Timer
    {
        id:showIntro2Timer;
        running: false;
        interval : 500;
        onTriggered:
        {
            //opacityAnim.start();
           // scaleAnim.start();
            brb.visible = true;
            brb.show();
            showIntro2Timer.stop();
        }
    }

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
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
        scaleAnim.from = 0;
        scaleAnim.to = 1;
        scaleAnim.start();

        mainText.opacity = 1;
        mainText.scale = 1;
        brb.visible = false;
        visible = true;
        gameResultScreen.animComplete();
        hideIntroTimer.start();

    }

    function stop()
    {
        brb.hide();
        visible = false;
        confirmExitPopup.hide();
        hideIntroTimer.stop();
        showIntro2Timer.stop();
    }
}
