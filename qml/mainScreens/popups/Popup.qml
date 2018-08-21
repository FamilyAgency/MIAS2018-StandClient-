import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"

Item
{
    id: core;
    anchors.fill: parent;
    visible: false;

    property int currentStageId: 0;
    property var greenColor:"#ffffff";
    property var blueColor:"#00aedc";

    FontManager
    {
        id: font;
    }

    DropShadow
    {
        anchors.fill: bg;
        horizontalOffset: 10;
        verticalOffset: 10;
        radius: 20.0;
        samples: 17;
        color: "#80000000";
        source: bg;
        opacity: 0.6;
    }

    Rectangle
    {
        visible: true;
        id: bg;
        color: blueColor;
        border.width: 0;
        implicitWidth: 900;
        implicitHeight: 900;
        radius: 450;
        smooth: true;
        antialiasing: true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        gradient: Gradient
        {
            GradientStop { position: 1.0; color: "#0b9abf" }
            GradientStop { position: 0.0; color: "#0aabd4" }
        }
    }

    Item
    {
        visible: false;
        id: preTask;
        smooth: true;
        antialiasing: true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        Text
        {
            id: countdownText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 300 * consts.designScale;
            color: "#ffffff";
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            text: "3";
        }
    }

    Item
    {
        id: postTask;
        visible: false;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        Text
        {
            id: stopText;

            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 35 * consts.designScale;
            font.letterSpacing: 14;

            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -280;

            color: greenColor;
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            text: "ОСТАНОВКА";
        }

        Text
        {
            id: descrText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -40;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 70;
            color: "#ffffff";
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            text: "";
        }

        Rectangle
        {
            id: polosa;
            color: greenColor;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: descrText.bottom;
            anchors.topMargin: 40;
            implicitWidth: 500;
            implicitHeight: 5;
            radius: 5;
        }

        Text
        {
            id: descrText2;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top:  polosa.bottom;
            anchors.topMargin: 40;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 35 * consts.designScale;
            color: greenColor;
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            text: "УЗНАЙ О ПРЕИМУЩЕСТВЕ<br/>НА ЭКРАНЕ";
        }

        Image
        {
            id: arrowIcon;
            visible: true;
            smooth: true;
            antialiasing: true;
            anchors.top:  descrText2.bottom;
            anchors.topMargin: 40;
            anchors.horizontalCenter: parent.horizontalCenter;
            source: "qrc:/resources/arrowpopup.png";
        }
    }

    Item
    {
        visible: false;
        id: allTask;
        smooth: true;
        antialiasing: true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;

        Image
        {
            id: placeIcon;
            visible: true;
            smooth: true;
            antialiasing: true;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -230;
            anchors.horizontalCenterOffset: 0;
            anchors.horizontalCenter: parent.horizontalCenter;
            //source: configController.getFileInAppDir("content/tasks/1.png");
        }

        Text
        {
            id: winDescrText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: placeIcon.bottom;
            anchors.topMargin: 10;
            //anchors.verticalCenter: parent.verticalCenter;
           // anchors.verticalCenterOffset: 70;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 70;
            color: "#ffffff";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
            text: "Ура! Ты проехал<br/>по маршруту<br/>до Третьяковской<br/>галереи";
            lineHeight: 0.9;
        }
    }

    ScaleAnimator
    {
        id:scaleAnimator;
        from: 0;
        to: 1;
        duration: 500
        running: false;
        easing.type: "InOutQuad";
        target: core;
    }

    Connections
    {
        target: superGameModule;
        onSuperGameStarted:
        {
            openCountDown();
        }

        onCountDownUpdate:
        {
            countDownUpdate(time);
        }

        onCountDownComplete:
        {
            visible = false;
        }
    }

    Connections
    {
        target: gameModule;

        onAllStagesComleteEventMap:
        {
            openGameComplete(description, imageWinName);
        }

        onStageComleteEventMap:
        {
            openStageComplete(description);
        }
    }

    Connections
    {
        target: gameTaskManager;

        onPreTaskStartEvent:
        {
            openCountDown();
        }

        onTaskStartEvent:
        {
            visible = false;
        }

        onPreTaskCoundownUpdate:
        {
            countDownUpdate(time);
        }
    }

    function openGameComplete(description, imageWinName)
    {
        preTask.visible = false;
        postTask.visible = false;
        allTask.visible = true;
        scale = 0;
        scaleAnimator.start();
        visible = true;

        winDescrText.text = description;
        console.log("allStagesComleteEventMap ", description, imageWinName);

        placeIcon.source = standData.getStandImage(imageWinName);
    }

    function openStageComplete(description)
    {
        descrText.text = description;

        preTask.visible = false;
        postTask.visible = true;
        allTask.visible = false;
        scale = 0;
        scaleAnimator.start();
        visible = true;
    }

    function openCountDown()
    {
        preTask.visible = true;
        postTask.visible = false;
        allTask.visible = false;
        scale = 0;
        scaleAnimator.start();
        visible = true;
    }

    function countDownUpdate(time)
    {
        countdownText.font.pixelSize = 350 * consts.designScale;
        countdownText.text = time.toFixed(0);

        if( countdownText.text == "0")
        {
            countdownText.font.pixelSize = 120 * consts.designScale;
            countdownText.text = "ПОЕХАЛИ";
        }
    }
}
