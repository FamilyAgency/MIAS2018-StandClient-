import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import "elements"
import "supergame"
import "../tools"

Item
{
    id: superGame;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string superGameTitle: "СУПЕРИГРА";
    property string descrTitleDefault: "Успейте проехать маршрут<br/> за ограниченное время.<br/>  Для победы нужна<br/> максимальная  концентрация.";
    property string buttonText: "ПОЕХАЛИ";

    property real btnMarginBottom: 100;

    signal animComplete();
    signal animStart();


    TitleBlock
    {
        id: title;
    }

    SupergameTimeRules
    {
        id: timeRules;
    }

    SupergameCountdown
    {
        id: supergameCountdown;
    }

    BigRedButton
    {
        id: startBtn;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 ;
        btnHeight: 350 ;
        btnRadius: 175 ;

        onClicked:
        {
            // core.animStart();
            superGameModule.startGame();
            startBtn.hide();
            title.hide();
            timeRules.hide();

            supergameCountdown.visible = true;
            supergameCountdown.show();
        }
    }

    Component.onCompleted:
    {
        startBtn.setTitle(buttonText);
        title.setTexts(superGameTitle, descrTitleDefault);
    }

    function start()
    {
        visible = true;
        superGame.animComplete();

        startBtn.visible = true;
        startBtn.show();

        title.visible = true;
        title.show();

        timeRules.visible = true;
        timeRules.show();
    }

    function stop()
    {
        visible = false;

        startBtn.visible = false;
        title.visible = false;
        timeRules.visible = false;
        supergameCountdown.visible = false;
    }
}
