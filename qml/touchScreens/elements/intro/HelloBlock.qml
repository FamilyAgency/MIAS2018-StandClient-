import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

import "../../.."
import "../../../components"
import ".."

Item
{
    id: data;
    anchors.fill: parent;
    opacity: 0;

    property string addTitleHelloText: "Познакомься с увлекательным,<br/>миром santa fe!<br/><br/>Представляешь,\
 управлять<br/>автомобилем santa fe стало<br/>возможно силой мысли!";
    property string buttonText: "НАЧНЕМ?";

    property real btnMarginBottom: 305 * consts.designScale;
    property real nameMarginTop: 294 * consts.designScale;
    property real titleMarginTop: 640 * consts.designScale;

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
        id: mainText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize:  90 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin:  nameMarginTop;
        anchors.top: parent.top;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        Layout.preferredWidth: 500;
        textFormat: Text.StyledText;
        elide: Text.ElideRight;
    }

    Text
    {
        id: addText;
        font.family: font.hyundaiSansHeadRegular;
        font.pixelSize: 54 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.topMargin:  titleMarginTop;
        anchors.top: parent.top;
        horizontalAlignment: Text.AlignHCenter;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible:false;
        anchors.fill: parent;

        onClicked:
        {
            introModule.startButtonClick();
        }
    }

    Timer
    {
        id: delayTimer;
        interval:1000;
        onTriggered:
        {
            opacityAnim.start();

            mainText.text = "Привет,<br/>" + userData.baseUserData.name;
            mainText.visible = true;
            addText.visible = true;
            addText.text = addTitleHelloText;
            brb.visible = true;
            brb.show();
        }
    }

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 1000
        running:false;
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonText);
    }

    function start()
    {

    }

    function startHelloState()
    {
        opacity = 0;
        delayTimer.restart();
    }

    function stop()
    {
        mainText.text =  "";
        addText.text =  "";

        mainText.visible = true;
        brb.visible = false;
    }
}
