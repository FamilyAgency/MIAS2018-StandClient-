import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8
import com.app 1.0

import "roulette"
import "elements"
import "../tools"

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
        id: consts;
    }

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

    Titles
    {
        id: titles;
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


    Component.onCompleted:
    {
        //sprite.source =  "qrc:/resources/arrow_pack.png";
        // sprite.start();
        brb.setTitle(rollTextDefault);

    }

    function start()
    {
        core.animComplete();
        brb.visible = true;
        brb.show();

        visible = true;
    }

    function stop()
    {
        visible = false;
        brb.visible = false;
    }
}
