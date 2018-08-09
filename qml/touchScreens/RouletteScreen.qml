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

//    Video
//    {
//        id: video;
//        width: parent.width;
//        height: parent.height;
//        loops: MediaPlayer.Infinite;
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.verticalCenter: parent.verticalCenter;
//        focus: true;
//        autoLoad: false;
//    }

    Roulette
    {
        id: roulette;
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

        onClicked:
        {
            core.animStart();
            rouletteModule.startRoll();
            brb.hide();
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

//    VideoManager
//    {
//        id: videos;
//    }

    Component.onCompleted:
    {
       // video.source = videos.bgLoop;
        brb.setTitle(rollTextDefault);
    }

    Connections
    {
        target: rouletteModule;

        onShowBrb:
        {
            core.animComplete();
            brb.visible = true;
            brb.show();
        }
    }

    function start()
    {
        brb.visible = false;
        visible = true;

        //video.seek(0);
        //video.play();
    }

    function stop()
    {
        visible = false;

       // video.stop();
        brb.visible = false;
    }
}
