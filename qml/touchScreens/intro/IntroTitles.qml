import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"
import "../../components"

Item
{ 
    property string mainTitleDefault: "SANTA FE.<br/>Управляй<br/>силой мысли!";
    property string addTitleDefault: "ПОЖАЛУЙСТА,<br/>ПРИЛОЖИТЕ БРАСЛЕТ<br/>К КРУГУ";

    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    Text
    {
        id: mainText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 120;
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
        font.pixelSize: 40;
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
        opacityAnim.stop();
        opacity = 0;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.duration = 2000;
        opacityAnim.start();
    }

    function hide()
    {
        opacityAnim.stop();
        opacityAnim.from = 1;
        opacityAnim.to = 0;
        opacityAnim.duration = 2000;
        opacityAnim.start();
    }
}
