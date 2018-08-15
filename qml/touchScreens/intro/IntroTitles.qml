import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"

Item
{
    anchors.fill: parent;

    property string mainTitleDefault: "Santa Fe.<br/>Управляй<br/>силой мысли";
    property string addTitleDefault: "ПОЖАЛУЙСТА,<br/>ПРИЛОЖИТЕ БРАСЛЕТ";


    FontManager
    {
        id: font;
    }

    Consts
    {
        id: consts;
    }

    Text
    {
        id: mainText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 120;// * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: mainTitleDefault;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        textFormat: Text.StyledText;
        lineHeight: 0.8;
    }

    Text
    {
        id: addText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40;// * consts.designScale;
        font.letterSpacing: 14;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: mainText.bottom;
        anchors.topMargin: 60;
        text: addTitleDefault;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        textFormat: Text.StyledText;

    }

    Item
    {
        id: animationItem
        anchors.fill: parent;
        Image
        {
            property int currentImage: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            id: image
            x: 0
            y: 0
            source: configController.getFileInAppDir("content/misc/redRound/round" + currentImage + ".png");
            NumberAnimation on currentImage
            {
                from: 1
                to: 29
                duration: 1000
                running: true;
                loops: Animation.Infinite;
            }
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 2000;
        running: false;
        easing.type: "InOutCubic";
    }

    function show()
    {
        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.duration = 2000;
        opacityAnim.start();
    }

    function hide()
    {
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.duration = 2000;
        opacityAnim.start();
    }

}
