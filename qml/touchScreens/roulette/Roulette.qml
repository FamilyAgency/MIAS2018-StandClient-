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
    property int circleSize : 300;

    FontManager
    {
        id: font;
    }

    Image
    {
        id: roullete
        width: 878 * consts.designScale;
        height: 875  * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: rouletteModule.circleY;
        smooth: true;
        source: "qrc:/resources/rulette.png";        
        rotation: rouletteModule.rotation;
        visible: rouletteModule.particlesVisibility;
    }

    Rectangle
    {
        id:bgPulsar;
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
        id:bg;
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

}
