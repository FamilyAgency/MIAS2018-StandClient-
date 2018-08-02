import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../../components"

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
        OpacityAnimator on opacity
        {
            id:mainOpacityAnim;
            from: 0;
            to: 1;
            running:false;
            duration: 500
        }
    }

    Text
    {
        id: helpText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
       // anchors.verticalCenterOffset: circleSize + 60;
        text: "А ТЕПЕРЬ ТЕБЕ НУЖНО<br/>КОНЦЕНТРИРОВАТЬСЯ<br/>НА АВТОМОБИЛЕ.<br/>ПОЕХАЛИ!";
        font.family: "Helvetica";
        font.pixelSize: 35;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
        visible:false;
        OpacityAnimator on opacity
        {
            id:hintOpactyAnimator;
            from: 0;
            to: 1;
            running:false;
            duration: 500
        }
    }

    function showMainTitle()
    {
        visible = true;
        mainText.opacity = 0;
        mainOpacityAnim.from = 0;
        mainOpacityAnim.to = 1;
        mainOpacityAnim.start();
    }

    function hideMainTitle()
    {
        mainOpacityAnim.from = 1;
        mainOpacityAnim.to = 0;
        mainOpacityAnim.start();
    }

}
