import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

import "../tools"

Item
{
    id:instruction;
    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "У С Т Р О Й С Т В О<br/>А К Т И В И Р О В А Н О";
    property string journeyTitleDefault: "отправляемся<br/>в путешествие";

    signal animComplete();
    signal animStart();

    Consts
    {
        id:consts;
    }

    FontManager
    {
        id: font;
    }

    Text
    {
        opacity: instructionModule.opacity1;
        id: mainText;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter:  parent.verticalCenter;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    Text
    {
        opacity: instructionModule.opacity2;
        id: journeyText;
        text: journeyTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter:  parent.verticalCenter;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
    }

    function start()
    {
        visible = true;
    }

    function stop()
    {
        visible = false;
    }
}
