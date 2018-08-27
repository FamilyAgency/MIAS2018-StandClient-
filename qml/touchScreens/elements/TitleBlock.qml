import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../../tools"

Item
{
    id: titleBlock;
    anchors.fill: parent;

    property int offsetY: 80;

    FontManager
    {
        id: font;
    }

    Text
    {
        id: text1;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40;
        color: "#0aabd4";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
        font.letterSpacing: 14;
    }

    Text
    {
        id: text2;
        anchors.top: text1.bottom;
        anchors.topMargin: titleBlock.offsetY;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    OpacityAnimator
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running: false;
        easing.type: "InOutCubic";
        target: titleBlock;
    }


    function setTexts(_text1, _text2)
    {
        text1.text = _text1;
        text2.text = _text2;
    }

    function show()
    {
        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();
    }

    function hide()
    {
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.start();
    }

}
