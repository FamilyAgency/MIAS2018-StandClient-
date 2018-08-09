import QtQuick 2.0
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import "../../tools"
import "../elements"

Item
{
    id: advatage;
    anchors.fill: parent;

    property string mainTitleDefault: "НАЗВАНИЕ<br/>ПРЕИМУЩЕСТВА";
    property int circleSize : 150;
    property real nameMarginTop: 200 * consts.designScale;
    property string buttonText: "ПОЕХАЛИ<br/>ДАЛЬШЕ!";
    property real btnMarginBottom: 305 * consts.designScale;

    signal advantageReaded;

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }

    Video
    {
        id: video;
        width : 1080;
        height : 600;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
    }

    Text
    {
        id: promtText;
        anchors.left: parent.left;
        anchors.leftMargin: 100 * consts.designScale;
        anchors.topMargin:  nameMarginTop;
        anchors.top: parent.top;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize:  70 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible:false;
        anchors.fill: parent;
        btnWidth: 410 * consts.designScale;
        btnHeight: 410 * consts.designScale;
        btnRadius: 205 * consts.designScale;

        onClicked:
        {
            advatage.advantageReaded();
            brb.hide();
        }
    }

    FullAdvantageDescription
    {
        id: fullAdvantageDescr;

        onAdvantageReaded:
        {
            advatage.advantageReaded();
        }
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonText);
    }

    function setTexts(title, description)
    {
        advatage.mainTitleDefault = title;
        fullAdvantageDescr.setTexts(title, description);
    }

    function setVideo(videoPath)
    {
        video.source = configController.getFileInAppDir(videoPath);
        video.play();
    }

    function show()
    {
        visible = true;
        fullAdvantageDescr.hide();
        brb.show();
    }

    function hide()
    {
        visible = false;
        video.stop();
        fullAdvantageDescr.hide();
    }
}
