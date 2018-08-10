import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

import "../../tools"
import "../elements"

Item
{
    id: core;
    anchors.fill: parent;
    opacity: 0;

    property string addTitleHelloText: "Познакомься с увлекательным,<br/>миром santa fe!<br/><br/>Представляешь,\
 управлять<br/>автомобилем santa fe стало<br/>возможно силой мысли!";
    property string buttonText: "НАЧНЕМ?";

    property real btnMarginBottom: 305 * consts.designScale;
    property real nameMarginTop: 294 * consts.designScale;
    property real titleMarginTop: 640 * consts.designScale;

    signal inAnimComplete();
    signal outAnimComplete();
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

    OpacityAnimator on opacity
    {
        id: opacityAnim;
        from: 0;
        to: 1;
        duration: 700;
        running:false;
        easing.type: "InOutCubic";

        onStopped:
        {
           opacity == 1 ? core.inAnimComplete() : core.outAnimComplete();
        }
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
            startOpacityAnim(1, 0);
            brb.hide();
        }
    }

    Timer
    {
        id: delayTimer;
        interval:2000;
        onTriggered:
        {
            startOpacityAnim(0, 1);
            mainText.text = "Привет,<br/>" + userData.baseUserData.name;
            brb.visible = true;
            brb.show();
        }
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonText);
    }

    function start()
    {

    }

    function startOpacityAnim(from, to)
    {
        opacityAnim.from = from;
        opacityAnim.to = to;
        opacityAnim.start();
        core.animStart();
    }

    function startHelloState()
    {
        mainText.visible = true;
        addText.visible = true;
        addText.text = addTitleHelloText;
        brb.setTitle(buttonText);

        opacity = 0;
        delayTimer.restart();
        core.animStart();
    }

    function startErrorState(errorMsg)
    {
        mainText.visible = false;
        addText.text = errorMsg;
        brb.setTitle("ОК");

        opacity = 0;
        delayTimer.restart();
        core.animStart();
    }

    function stop()
    {
        mainText.text =  "";
        addText.text =  "";

        mainText.visible = true;
        brb.visible = false;
    }
}
