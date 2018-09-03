import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"

Item
{
    id: core;

    property alias btnAnchors: backBtn.anchors;
    signal clicked;

    anchors.fill: parent;

    FontManager
    {
        id: font;
    }

    Button
    {
        id: backBtn;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.horizontalCenterOffset: 20;

        contentItem: Text
        {
            text: "В НАЧАЛО";
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            opacity: 0;
            implicitHeight: 100;
            implicitWidth: 200;
        }

        onClicked:
        {
            core.clicked();
        }
    }

    Image
    {
        source:"qrc:/resources/arrow-small.png";
        anchors.right:backBtn.left;
        anchors.rightMargin: -20;
        anchors.verticalCenter: backBtn.verticalCenter;

    }

    OpacityAnimator on opacity
    {
        id: opacityAnim1;
        from: 0;
        to: 1;
        duration: 700;
        running: false;
        easing.type: "InOutCubic";
    }

    function show()
    {
        opacity = 0;
        opacityAnim1.from = 0;
        opacityAnim1.to = 1;
        opacityAnim1.start();
    }

    function hide()
    {
        opacityAnim1.from = 1;
        opacityAnim1.to = 0;
        opacityAnim1.start();
    }

}
