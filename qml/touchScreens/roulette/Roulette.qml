import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

import "../../tools"
import "../elements"

Item
{
    anchors.fill: parent;
    property int circleSize: 300;
    property int offset: 70;
    property int vertOffset: 0;

    FontManager
    {
        id: font;
    }

    Image
    {
        id: roullete
        width: 926 * consts.designScale;
        height: 926  * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        smooth: true;
        source: "qrc:/resources/rulette.png";
        rotation: rouletteModule.rotation;
        visible: rouletteModule.particlesVisibility;

        Image
        {
            id: image1;
            scale: rouletteModule.allIconsScale;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: -offset;
            smooth: true;
            rotation: -rouletteModule.rotation;
            source: standData.getStandImage("task3/icon.png");
        }

        Image
        {
            id: image2;
            rotation: -rouletteModule.rotation;
            scale: rouletteModule.allIconsScale;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: vertOffset;
            anchors.left: parent.left;
            anchors.leftMargin: -offset;
            smooth: true;
            source: standData.getStandImage("task1/icon.png");
        }

        Image
        {
            id: image3;
            rotation: -rouletteModule.rotation;
            scale: rouletteModule.allIconsScale;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.verticalCenterOffset: vertOffset;
            anchors.right: parent.right;
            anchors.rightMargin: -offset;
            smooth: true;
            source: standData.getStandImage("task2/icon.png");
        }
    }

    Rectangle
    {
        id: bgPulsar;
        implicitHeight: 1200 * consts.designScale;
        implicitWidth: 1200 * consts.designScale;

        color: "#7b7cfe";
        radius: 600 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY - 125;
        scale: rouletteModule.pulsarScale;
        opacity: 1 - rouletteModule.pulsarScale;
    }

    Rectangle
    {
        id: bg;
        implicitHeight: 950 * consts.designScale;
        implicitWidth: 950 * consts.designScale;
        radius: 475 * consts.designScale;

        color:  "#7b7cfe";

        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        scale: rouletteModule.scale;
        opacity: rouletteModule.circleOpacity;
    }

    Image
    {
        id: choosen
        visible: rouletteModule.mainIconVisibility;
        scale: rouletteModule.mainIconScale;
        opacity: rouletteModule.mainIconOpacity;

        anchors.horizontalCenter: roullete.horizontalCenter;
        anchors.top: roullete.top;
        anchors.topMargin: -offset + rouletteModule.mainIconY;
        smooth: true;
    }

    MindwaveAttention
    {
        y: 100;
        id: mindwaveAttention;
        visible: false;
        opacity: rouletteModule.mindwaveCtrlOpacity;
        Component.onCompleted:
        {
            mindwaveAttention.setLocation(0.0, 60.0);
        }

        onAttentionGood:
        {
            rouletteModule.finalizeCarAnimation();
        }
    }

    Connections
    {
        target: rouletteModule;

        onUpdateChoosenCategoryImagePath:
        {
            choosen.source = standData.getStandImage(path);
        }
    }

    function show()
    {
        mindwaveAttention.visible = true;
    }

    function hide()
    {
        mindwaveAttention.visible = false;
        mindwaveAttention.hide();
    }
}
