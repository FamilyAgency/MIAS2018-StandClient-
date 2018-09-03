import QtQuick 2.2

import "../../tools"
import "../elements"
import "../../components"

import Qt3D.Extras 2.0

Item
{  
    property string mainTitleDefault: "ВЫБЕРИТЕ МАРШРУТ";
    property string descrTitleDefault: "Вас ждут три остановки, на которых<br/>вы узнаете об уникальных<br/> преимуществах нового SANTA FE.";
    property string mainTitle2: "Концентрируйтесь<br/>на Hyundai SANTA FE.<br/><br/>Автомобиль начнет движение<br/>и появится на карте.";

    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    TitleBlock
    {
        id: title;
        opacity:  rouletteModule.mainTitleOpacity
    }

    Component.onCompleted:
    {
        title.setTexts(mainTitleDefault, descrTitleDefault);
        title.setDescrFontSize(40);
        title.offsetY = 40;
    }

    Text
    {
        id: taskTextTitle;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.verticalCenterOffset: -180;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        // textFormat: Text.StyledText;
        text: "ВАШ МАРШРУТ";
        font.letterSpacing: 14;
        opacity: rouletteModule.taskOpacity * 0.7;
    }

    Text
    {
        id: taskText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: taskTextTitle.top;
        anchors.topMargin: 80;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        textFormat: Text.StyledText;
        opacity: rouletteModule.taskOpacity;
        lineHeight: 0.9;
    }

    Text
    {
        id: helpText;
        anchors.top: parent.top;
        anchors.topMargin: 168;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitle2;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 50;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        opacity: rouletteModule.helpTextOpacity;
    }

    AnimationPlayer
    {
        id: animationItem;
        currentImage: 1;
        endFrame: 35;
        startFrame: 4;
        opacity: rouletteModule.helpTextOpacity;

        Component.onCompleted:
        {
            animationItem.setSource("content/misc/arrow/", ".png");
            animationItem.setFPS(30);
            animationItem.setRunning(false);
            animationItem.setLocation((1080 - 200) * 0.5, 0)
            animationItem.init();
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
