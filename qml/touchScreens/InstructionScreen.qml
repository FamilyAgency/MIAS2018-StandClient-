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

    property string mainTitleDefault: "УСТРОЙСТВО<br/>АКТИВИРОВАНО";
    property string journeyTitleDefault: "Осталось выбрать<br/>маршрут в городе.<br/><br/>Вас ждут три остановки,<br/> на которых вы узнаете<br/> об уникальных преимуществах<br/> нового SANTA FE.";

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
        font.letterSpacing: 14;
    }

//    Text
//    {
//        opacity: instructionModule.opacity2;
//        id: journeyText;
//        text: journeyTitleDefault;
//        font.family: font.hyundaiSansHeadRegular;
//        font.pixelSize: 54 * consts.designScale;
//        color: "#ffffff";
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.verticalCenter:  parent.verticalCenter;
//        horizontalAlignment: Text.AlignHCenter;
//        verticalAlignment: Text.AlignVCenter;
//       // font.letterSpacing: 14;
//    }

    function start()
    {
        visible = true;
    }

    function stop()
    {
        visible = false;
    }
}
