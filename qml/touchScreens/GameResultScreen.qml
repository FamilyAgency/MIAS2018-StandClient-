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

    property string mainTitleDefault: "Ура, до получения<br/>приза совсем немного!<br/>Осталось выполнить<br/>одно задание.";
    property string buttonTakeColaText: "НЕТ, СПАСИБО";
    property string buttonSuperGameText: "ХОЧУ<br/>СЫГРАТЬ";

    property string superGameTitle: "СУПЕРИГРА";
    property string descrTitleDefault: "Готовы бороться за приз?<br/>Тогда начнем!";

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
            easing.type: "OutCubic";
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
            gameResultModule.superGameAcceptedButtonClick();
            brb.hide();
            title.hide();
        }
    }

    TitleBlock
    {
        id: title;
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

    Timer
    {
        id:hideIntroTimer;
        running: false;
        interval: 6000;
        onTriggered:
        {
            opacityAnim.from = 1;
            opacityAnim.to = 0;
            opacityAnim.start();
            scaleAnim.from = 1;
            scaleAnim.to = 0.2;
            scaleAnim.start();
            hideIntroTimer.stop();
            showIntro2Timer.start();
        }
    }

    Timer
    {
        id:showIntro2Timer;
        running: false;
        interval: 2000;
        onTriggered:
        {
            brb.visible = true;
            brb.show();

            title.visible = true;
            title.show();

            showIntro2Timer.stop();
        }
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonSuperGameText);
        title.setTexts(superGameTitle, descrTitleDefault);
    }

    function start()
    {
       // backBtn.opacity = 0;
       // backBtn.visible = false;

        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
        scaleAnim.from = 0;
        scaleAnim.to = 1;
        scaleAnim.start();

        mainText.opacity = 1;
        mainText.scale = 1;

        visible = true;
        gameResultScreen.animComplete();
        hideIntroTimer.start();
    }

    function stop()
    {
        brb.visible = false;
        title.visible = false;

        visible = false;
        confirmExitPopup.hide();
        hideIntroTimer.stop();
        showIntro2Timer.stop();
    }
}
