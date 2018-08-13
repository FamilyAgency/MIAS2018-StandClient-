import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import "../../tools"

Item
{
    id: core;
    anchors.fill: parent;

    property alias btnAnchors: backBtn.anchors;
    signal clicked;

    FontManager
    {
        id: font;
    }

    Button
    {
        id: backBtn;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: "В НАЧАЛО";
            font.family: font.hyundaiSansHeadMedium;
            font.pixelSize: 20 * consts.designScale;
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
