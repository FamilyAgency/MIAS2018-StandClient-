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

    signal animComplete();
    signal animStart();

    property string mainTitleDefault: "Отлично!<br/>  Вы познакомились<br/> с преимуществами <br/>нового Hyundai SANTA FE.";
    property string buttonSuperGameText: "ГОТОВ";

    property string superGameTitle: "СУПЕРИГРА";
    property string descrTitleDefault: "До получения приза <br/>осталось совсем немного!<br/> Продолжайте путешествие <br/>c Hyundai SANTA FE.";

    property real btnMarginBottom: 100;

    signal startSuperGame();
    signal getColaCan();

    anchors.fill: parent;

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
        font.pixelSize: 60 ;
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
        btnWidth: 350;
        btnHeight: 350;
        btnRadius: 175;

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
            opacityAnim.stop();
            scaleAnim.stop();

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
        opacityAnim.stop();
        scaleAnim.stop();

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
