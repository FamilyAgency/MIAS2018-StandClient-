import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import "elements"
import "../tools"

Item
{
    id: superGame;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "СУПЕРИГРА";
    property string descrTitleDefault: "Успей проехать трассу<br/>на время, от тебя нужна<br/>максимальна <br/>концентрация";
    property string buttonText: "ПОЕХАЛИ";
    property string timeTextDefault: "2<br/>МИНУТЫ";
    property string triesTextDefault: "1<br/>ПОПЫТКА";
    property real btnMarginBottom: 100 * consts.designScale;

    signal animComplete();
    signal animStart();

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }

    Text
    {
        id: mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#990000";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: descrText;
        anchors.top: mainText.bottom;
        anchors.topMargin: 100 * consts.designScale;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: descrTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 80 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    Text
    {
        id: timeText;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: timeTextDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignHCenter;
    }

    Text
    {
        id: triesText;
        anchors.top: timeText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: triesTextDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    BigRedButton
    {
        id: startBtn;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

        onClicked:
        {
           // core.animStart();
           // rouletteModule.startRoll();
            superGameModule.startGame();
            startBtn.hide();
        }
    }

    Component.onCompleted:
    {
        startBtn.setTitle(buttonText);
    }

//    Button
//    {
//        id: startBtn;

//        anchors.top: triesText.bottom;
//        anchors.topMargin: 100;
//        anchors.horizontalCenter: parent.horizontalCenter;

//        contentItem: Text
//        {
//            text: buttonText;
//            font.family: "Helvetica";
//            font.pixelSize: 25;
//            color: "#ffffff"
//            horizontalAlignment: Text.AlignHCenter;
//            verticalAlignment: Text.AlignVCenter;

//        }

//        background: Rectangle
//        {
//            implicitHeight: 200;
//            implicitWidth: 400;
//            color: startBtn.down ? "#3c2755" : "#4e1a8a";
//        }

//        onClicked:
//        {
//            superGameModule.startGame();
//            startBtn.visible = false;
//            mainText.visible = false;
//            descrText.visible = false;
//            triesText.visible = false;
//            passBtn.visible = true;
//        }
//    }

    Button
    {
        id: passBtn;

        anchors.top: triesText.bottom;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;

        contentItem: Text
        {
            text: "ПРОЙТИ СУПЕРИГРУ";
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
        }

        background: Rectangle
        {
            implicitHeight: 200;
            implicitWidth: 400;
            color: passBtn.down ? "#3c2755" : "#4e1a8a";
        }

        onClicked:
        {
            superGameModule.superGamePassedTest();
        }
    }

    Connections
    {
        target: superGameModule;
        onUpdateSuperGameTime:
        {
            var minutes = (mills/1000.).toFixed(1);
            timeTextDefault = minutes / 60. + "<br/>МИНУТЫ";
            timeText.text = minutes;
        }

        onSuperGameFailed:
        {
            console.log("SuperGameFailed");
        }

        onSuperGameSuccess:
        {
            console.log("onSuperGameSuccess");      
        }
    }

    function start()
    {
        visible = true;
        superGame.animComplete();
        startBtn.visible = true;
        startBtn.show();
    }

    function stop()
    {
        visible = false;
        timeText.text = timeTextDefault;
        startBtn.visible = false;
        mainText.visible = true;
        descrText.visible = true;
        triesText.visible = true;
        passBtn.visible = false;
    }
}
