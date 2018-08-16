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
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -280;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 35 * consts.designScale;
            color: greenColor;
            textFormat: Text.StyledText;
            horizontalAlignment :Text.AlignHCenter;
            text: "О С Т А Н О В К А";
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
            source: "qrc:/resources/arrow.png";
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
            anchors.verticalCenterOffset: -410;
            anchors.horizontalCenterOffset: -100;
            anchors.horizontalCenter: parent.horizontalCenter;
            //source: configController.getFileInAppDir("content/tasks/1.png");
        }

        Text
        {
            id: winDescrText;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: 80;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 70;
            color: "#ffffff";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
            text: "Ура! Ты проехал<br/>по маршруту<br/>до Третьяковской<br/>галереи";
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
        target: gameModule;

        onAllStagesComleteEventMap:
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

        onStageComleteEventMap:
        {
            descrText.text = description;

            preTask.visible = false;
            postTask.visible = true;
            allTask.visible = false;
            scale = 0;
            scaleAnimator.start();
            visible = true;
        }
    }

    Connections
    {
        target: gameTaskManager;

        onPreTaskStartEvent:
        {
            // currentStageId = userData.getCurrentStageId();
            preTask.visible = true;
            postTask.visible = false;
            allTask.visible = false;
            scale = 0;
            scaleAnimator.start();
            visible = true;
        }

        onTaskStartEvent:
        {
            visible = false;
        }

        onPreTaskCoundownUpdate:
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

}