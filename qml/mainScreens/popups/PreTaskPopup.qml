import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"

Item
{
    id:core;
    anchors.fill: parent;
    property int currentStageId: 0;

    visible:false;

    FontManager
    {
        id: font;
    }

    Image
    {
        id: preTask;
        smooth:true;
        antialiasing: true;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        source: configController.getFileInAppDir("content/misc/bluecircle.png");

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

    Image
    {
        id: postTask;
        visible:false;
        smooth:true;
        antialiasing: true
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        source: configController.getFileInAppDir("content/misc/stop.png");
    }

    Image
    {
        id: allTask;
        visible:false;
        smooth:true;
        antialiasing: true
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        source: configController.getFileInAppDir("content/misc/fin.png");
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
        target:gameModule;

        onAllStagesComleteEvent:
        {
            preTask.visible = false;
            postTask.visible = false;
            allTask.visible = true;
            scale = 0;
            scaleAnimator.start();
            visible = true;
        }
    }

    Connections
    {
        target:gameTaskManager;

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

        onTaskComleteEvent:
        {
            preTask.visible = false;
            postTask.visible = true;
            allTask.visible = false;
            scale = 0;
            scaleAnimator.start();
            visible = true;
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
