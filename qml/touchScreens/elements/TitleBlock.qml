import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../../tools"

Item
{
    anchors.fill: parent;

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
        id: text1;
        anchors.top: parent.top;
        anchors.topMargin: 100 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#990000";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }


    Text
    {
        id: text2;
        anchors.top: text1.bottom;
        anchors.topMargin: 80 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 80 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
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
