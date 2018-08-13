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
    property string journeyTitleDefault: "отправляемся<br/>в путешествие";
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

            onStopped:
            {
                console.log("first text opacity", mainText.opacity)
                if(mainText.opacity === 0)
                {
                    journeyOpacityAnim.duration = 1000;
                    journeyOpacityAnim.from = 0;
                    journeyOpacityAnim.to = 1;
                    journeyOpacityAnim.start();
                }
            }
        }
    }

    Text
    {
        opacity: 0;
        id: journeyText;
        text: journeyTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 60 * consts.designScale;
        color: "#ffffff";
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter:  parent.verticalCenter;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;

        OpacityAnimator on opacity
        {
            id: journeyOpacityAnim;
            from: 0;
            to: 1;
            duration: 2000
            running:false;

            onStopped:
            {
                if(journeyText.opacity === 1)
                {
                    hideJourneyTimer.start();
                }
            }
        }

        Timer
        {
            id:hideJourneyTimer;
            interval: 1000;
            running: false;
            onTriggered:
            {
                journeyOpacityAnim.duration = 700;
                journeyOpacityAnim.from = 1;
                journeyOpacityAnim.to = 0;
                journeyOpacityAnim.start();
            }
        }
    }

    Timer
    {
        id:hideTextTimer;
        interval: 3000;
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
            finishInstructTimer.stop();
            instructionModule.rouletteButtonClick();
        }
    }

    function start()
    {
        goodSignal = false;
        visible = true;
        hideTextTimer.start();
        finishInstructTimer.start();
        mainTitleDefault.opacity = 0;
        journeyText.opacity = 0;

        mind.onPoorSignalLevelChanged.connect(poorSignalLevelChanged)

        //        if(goodSignal)
        //        {
        //            goodSignalHandler();
        //        }
    }

    function stop()
    {
        hideTextTimer.stop();
        finishInstructTimer.stop();
        hideJourneyTimer.stop();
        visible = false;
        mainTitleDefault.opacity = 0;
        journeyText.opacity = 0;

        journeyOpacityAnim.stop();
        textOpacityAnim.stop();

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
