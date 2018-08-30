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

    property int canvasSize: 950;

    property string bgColor:"#7b7cfe";

    FontManager
    {
        id: font;
    }

    Image
    {
        id: roullete
        width: 926;
        height: 926;
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
        implicitHeight: 1200;
        implicitWidth: 1200;

        color: bgColor
        radius: 600;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY - 125;
        scale: rouletteModule.pulsarScale;
        opacity: 1 - rouletteModule.pulsarScale;
    }

    Rectangle
    {
        id: bg;
        implicitHeight: 950;
        implicitWidth: 950;
        radius: 475;

       // color:bgColor;

        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        scale: rouletteModule.scale;
        opacity: rouletteModule.circleOpacity;

        gradient: Gradient
        {
            GradientStop { position: 1.0; color: "#0178a4" }
            GradientStop { position: 0.0; color: "#0b82c0" }
        }
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
        id: mindwaveAttention;
        visible: false;
        opacity: rouletteModule.mindwaveCtrlOpacity;

        canvasWidth: canvasSize;
        canvasHeight: canvasSize;
        canvasHalfWidth: canvasSize * 0.5;
        canvasHalfHeight: canvasSize * 0.5;

        Component.onCompleted:
        {
            mindwaveAttention.setLocation(1080 * 0.5 - canvasHalfWidth, 1920 * 0.5 - canvasHalfHeight + 50);
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

        onMindwaveAttentionThresholdUpdate:
        {
            mindwaveAttention.attentionThreshold = attention/100.;
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
