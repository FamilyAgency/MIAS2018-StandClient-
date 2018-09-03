import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

import "supergame"

Item
{
    id: result;

    signal animComplete();
    signal animStart();

    anchors.fill: parent;
    anchors.centerIn: parent;  

    SuperGameSuccessScreen
    {
        id:superGameSuccessScreen;
        visible: false;

        onGotoIntro:
        {
            superGameSuccessScreen.hide();
            outTimer.start();
        }
    }

    SuperGameFailScreen
    {
        id:superGameFailScreen;
        visible: false;

        onGotoIntro:
        {
            superGameFailScreen.hide();
            outTimer.start();
        }
    }

    Timer
    {
        id: outTimer;
        interval: 1000;
        running: false;
        onTriggered:
        {
            outTimer.stop();
            superGameResultModule.superGameResultReadedButtonClicked();
        }
    }

    Connections
    {
        target: superGameModule;

        onSuperGameFailed:
        {
            superGameFailedHandler();
        }

        onSuperGameSuccess:
        {
           superGameSuccessHandler();
        }
    }

    function start()
    {
        visible = true;
        result.animComplete();

       // superGameFailedHandler();
       // superGameSuccessHandler();
    }

    function stop()
    {
        visible = false;
        outTimer.stop();
    }

    function superGameSuccessHandler()
    {
        superGameSuccessScreen.visible = true;
        superGameFailScreen.visible = false;
        superGameSuccessScreen.show();
    }

    function superGameFailedHandler()
    {
        superGameSuccessScreen.visible = false;
        superGameFailScreen.visible = true;
        superGameFailScreen.show();
    }
}
