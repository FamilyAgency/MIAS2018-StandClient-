import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "results"

Item
{
    id: result;
    anchors.fill: parent;
    anchors.centerIn: parent;

    signal animComplete();
    signal animStart();

    SuperGameSuccessScreen
    {
       id:superGameSuccessScreen;

       onGotoIntro:
       {
           appController.backToIntro();
       }
    }

    SuperGameFailScreen
    {
       id:superGameFailScreen;
       visible: false;
    }

    Connections
    {
        target: superGameModule;

        onSuperGameFailed:
        {
            superGameSuccessScreen.visible = false;
            superGameFailScreen.visible = true;
            console.log("SuperGameFailed");
        }

        onSuperGameSuccess:
        {
            superGameSuccessScreen.visible = true;
            superGameFailScreen.visible = false;
            console.log("onSuperGameSuccess");
        }
    }

    function start()
    {
        visible = true;
        result.animComplete();
    }

    function stop()
    {
        visible = false;
    }
}
