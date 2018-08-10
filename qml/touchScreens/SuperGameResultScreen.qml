import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "supergame"

Item
{
    id: result;
    anchors.fill: parent;
    anchors.centerIn: parent;

    signal animComplete();
    signal animStart();

    property bool superGameSuccess: false;

    SuperGameSuccessScreen
    {
        id:superGameSuccessScreen;

        onGotoIntro:
        {
            superGameSuccess = true;
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
            superGameSuccess = false;
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
            if(superGameSuccess)
            {
                superGameResultModule.superGameResultReadedButtonClicked();
            }
            else
            {
                appController.backToIntro();
            }
        }
    }

    Connections
    {
        target: superGameModule;

        onSuperGameFailed:
        {
            superGameSuccessScreen.visible = false;
            superGameFailScreen.visible = true;
            superGameFailScreen.show();
            console.log("SuperGameFailed");
        }

        onSuperGameSuccess:
        {
            superGameSuccessScreen.visible = true;
            superGameFailScreen.visible = false;
            superGameSuccessScreen.show();
            console.log("onSuperGameSuccess");
        }
    }

    function start()
    {
        visible = true;
        result.animComplete();

       // superGameSuccessScreen.visible = false;
       /// superGameFailScreen.visible = true;
       /// superGameFailScreen.show();
    }

    function stop()
    {
        visible = false;
    }
}
