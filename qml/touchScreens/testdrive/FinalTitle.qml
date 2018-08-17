import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../../tools"

Item
{
    property string okText: "Спасибо!<br/>Ваш запрос отправлен.";

    anchors.fill: parent;
    anchors.centerIn: parent;

    FontManager
    {
        id: font;
    }

    Consts
    {
        id: consts;
    }


    Text
    {
        id: okFiled;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: okText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 80 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;

        OpacityAnimator on opacity
        {
            id: opacityAnim;
            from: 0;
            to: 1;
            duration: 700;
            running: false;
            easing.type: "InOutCubic";

            onStopped:
            {
                if( okFiled.opacity == 0)
                {
                    appController.backToIntro();
                }
            }
        }

        ScaleAnimator on scale
        {
            id: scaleAnim;
            from: 0.5;
            to: 1;
            duration: 700;
            running:false;
            easing.type: "OutCubic";
        }
    }

    Timer
    {
        id:outTimer;
        running: false;
        interval: 2000;
        onTriggered:
        {

            opacityAnim.from = 1;
            opacityAnim.to = 0;
            opacityAnim.start();

            scaleAnim.from = 1;
            scaleAnim.to = 0;
            scaleAnim.start();
        }
    }

    function show()
    {
        visible = true;
        opacityAnim.from = 0;
        opacityAnim.to = 1;
        opacityAnim.start();

        scaleAnim.from = 0.5;
        scaleAnim.to = 1;
        scaleAnim.start();

        outTimer.start();
    }

    function hide()
    {
        visible = false;
        okFiled.scale = 0;
        okFiled.opacity = 0;
        outTimer.stop();
    }

}
