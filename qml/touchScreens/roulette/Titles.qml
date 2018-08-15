import QtQuick 2.2

import "../../tools"
import "../elements"

import Qt3D.Extras 2.0

Item
{
    anchors.fill: parent;

    property string mainTitleDefault: "Выбери уникальный<br/>маршрут";

    FontManager
    {
        id: font;
    }

    Text
    {
        id: mainText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60 * consts.designScale;
        color: "#ffffff";
        anchors.top: parent.top;
        anchors.topMargin: 168 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        textFormat: Text.StyledText;
        opacity:  rouletteModule.mainTitleOpacity
    }

    Text
    {
        id: taskText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -10;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        textFormat: Text.StyledText;
        opacity: rouletteModule.taskOpacity;

        Text
        {
            id: taskTextTitle;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 40 * consts.designScale;
            color: "#ffffff";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: -120;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            // textFormat: Text.StyledText;
            opacity : 0.7;
            text: "В А Ш   М А Р Ш Р У Т";
        }
    }

    Text
    {
        id: helpText;
        anchors.top: parent.top;
        anchors.topMargin: 168 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: "А теперь тебе нужно<br/>концентрироваться<br/>на автомобиле.<br/>Поехали!";
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        opacity: rouletteModule.helpTextOpacity;
    }

    Item
    {
        id: animationItem
        anchors.fill: parent;
        opacity: rouletteModule.helpTextOpacity;
        Image
        {
            property int currentImage: 1
            anchors.horizontalCenter: parent.horizontalCenter
            id: image
            x: 0
            y: 0
            source: configController.getFileInAppDir("content/misc/arrow/" + currentImage + ".png");
            NumberAnimation on currentImage
            {
                from: 4
                to: 35
                duration: 1000
                running: true;
                loops: Animation.Infinite;
            }
        }
    }

    Connections
    {
        target: userData;

        onGameUserDataChanged:
        {
            taskText.text = userData.gameUserData.description;
        }
    }
}
