import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8
import com.app 1.0

import ".."
import "../components"
import "elements"
import "elements/roulette"

Item
{    
    id:core;

    anchors.fill: parent;

    property string rollTextDefault: "КРУТИТЬ<br/>РУЛЕТКУ";
    property real btnMarginBottom: 100 * consts.designScale;

    signal animComplete();
    signal animStart();

    Consts
    {
        id:consts;
    }

    Video
    {
        id: video;
        width: parent.width;
        height: parent.height;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
    }

    Roulette
    {
        id: roulette;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible:false;
        anchors.fill: parent;

        onClicked:
        {
            if(rouletteModule.state == RouletteState.Roll)
            {
                core.animStart();
                rouletteModule.startRoll();
                brb.hide();
            }
        }
    }

    Image
    {
        id: car
        anchors.horizontalCenter: parent.horizontalCenter;
        smooth: true;
        source: "qrc:/resources/santafe_top.png"
        y: parent.height + rouletteModule.carY;
        width: 251 * consts.designScale;
        height: 555 * consts.designScale;
    }

    Titles
    {
        id: titles;
    }

    Component.onCompleted:
    {
        video.source = configController.getFileInAppDir("content/video/bgloop.mp4");
        brb.setTitle(rollTextDefault);
        brb.setWidth(350);
    }

    Connections
    {
        target: rouletteModule;

        onStateChanged:
        {
            console.log(":::::::::::: state changed::::::::::::", rouletteModule.state)

            switch(rouletteModule.state)
            {
            case RouletteState.Intro:
                brb.visible = false;
                break;

            case RouletteState.Roll:
                brb.visible = true;
                brb.show();
                core.animComplete();
                break;

            case RouletteState.RollFinished:
                core.animStart();
                break;

            case RouletteState.CarStarting:
                break;
            }
        }
    }

    function start()
    {
        visible = true;
        video.play();
    }

    function stop()
    {
        visible = false;

        video.seek(0);
        video.pause();
        brb.visible = false;
    }
}
