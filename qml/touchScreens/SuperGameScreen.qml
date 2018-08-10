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
    property string descrTitleDefault: "Успей проехать трассу<br/>на время, от тебя нужна<br/>максимальна <br/>концентрация";

    property string buttonText: "ПОЕХАЛИ";

    property real btnMarginBottom: 100 * consts.designScale;

    signal animComplete();
    signal animStart();

    Consts
    {
        id: consts;
    }

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
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

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
