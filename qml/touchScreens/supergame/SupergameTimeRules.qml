import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../../tools"

Item
{
    anchors.fill: parent;
    anchors.centerIn: parent;

    property string timeTextDefault: "2:00";
    property string triesTextDefault: "1";  

    Tools
    {
        id: tools;
    }

    FontManager
    {
        id: font;
    }

    Image
    {
        id: time
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;

        smooth: true;
        source: "qrc:/resources/Time.png"
    }

    Text
    {
        id: timeText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: -230;
        anchors.verticalCenterOffset: 30;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 160;
        text: timeTextDefault;

        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;

        Text
        {
            id: timeText2;
            anchors.horizontalCenter: timeText.horizontalCenter;
            anchors.top: timeText.bottom;
            anchors.topMargin: -10;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 40;
            text: "МИНУТЫ";
            color: "#0aabd4";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
        }
    }

    Text
    {
        id: triesText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: 210;
        anchors.verticalCenterOffset: 30;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 160;
        text: triesTextDefault;        
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;

        Text
        {
            id: triesText2;
            anchors.horizontalCenter: triesText.horizontalCenter;
            anchors.top: triesText.bottom;
            anchors.topMargin: -10;
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 40;
            text: "ПОПЫТКА";
            color: "#0aabd4";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignHCenter;
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running: false;
        easing.type: "InOutCubic";
    }

    function show()
    {
        timeText.text = tools.formatSeconds1(superGameModule.getSuperGameTime() / 1000.0);
        opacityAnim.stop();
        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
    }

    function hide()
    {
        opacityAnim.stop();
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.start();
    }
}
