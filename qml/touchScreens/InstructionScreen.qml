import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8

import "../tools"

Item
{
    id:instruction;

    anchors.fill: parent;

    property string mainTitleDefault: "У С Т Р О Й С Т В О<br/>А К Т И В И Р О В А Н О";
    property bool goodSignal: false;

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
        opacity: 0;
        id: mainText;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 40 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter:  parent.verticalCenter;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        OpacityAnimator on opacity
        {
            id: textOpacityAnim;
            from: 0;
            to: 1;
            duration: 2000
            running:false;

        }
    }

    Timer
    {
        id:hideTextTimer;
        interval: 2000;
        running: false;
        onTriggered:
        {
            textOpacityAnim.duration = 1000;
            textOpacityAnim.from = 1;
            textOpacityAnim.to = 0;
            textOpacityAnim.start();
            hideTextTimer.stop();
        }
    }

    Timer
    {
        id:finishInstructTimer;
        interval: 9000;
        running: false;
        onTriggered:
        {
            instructionModule.rouletteButtonClick();
        }
    }

    function start()
    {
        visible = true;
        hideTextTimer.start();
        finishInstructTimer.start();

        mind.onPoorSignalLevelChanged.connect(poorSignalLevelChanged)

        //        if(goodSignal)
        //        {
        //            goodSignalHandler();
        //        }
    }

    function stop()
    {
        //instructionVideoHolder.stop();
        visible = false;

        mind.onPoorSignalLevelChanged.disconnect(poorSignalLevelChanged)
    }

    function poorSignalLevelChanged()
    {
        var level = mind.poorSignalLevel;
        console.log("signal level : ", level);
        if( !goodSignal && level === 100)
        {
            goodSignal = true;
            goodSignalHandler();

        }
        if (goodSignal && level < 100)
        {
            goodSignal = false;
        }
    }

    function goodSignalHandler()
    {
        // instructionVideoHolder.signalIsGood();
        mainText.opacity = 0;
        textOpacityAnim.duration = 1000;
        textOpacityAnim.from = 0;
        textOpacityAnim.to = 1;
        textOpacityAnim.start();
    }
}
