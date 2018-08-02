import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

import com.app 1.0
import "elements/intro"

Item
{
    id:intro;
    anchors.fill: parent;
    anchors.centerIn: parent;

    signal animComplete();
    signal animStart();

    VideoHolder
    {
        id: videoHolder;
    }

    HelloBlock
    {
        id: helloBlock;
    }

    Component.onCompleted:
    {

    }

    Connections
    {
        target:introModule;

        onUserStartPlay:
        {
            videoHolder.startHelloState();
            helloBlock.startHelloState();
        }

        onUserNotFound:
        {
            mainText.text = "Похоже, что тебя<br/>не существует!";
            cantPlayHandler();
        }

        onUserCantStartReason:
        {
            console.log("cant start reason ::: ", userData.getReasonCantPlay(), reason);

            switch(reason)
            {
            case CantPlayReason.WasRecently:
                mainText.text = "Недавно же играл!";
                break;

            case CantPlayReason.YouArePlaying:
                mainText.text = "Играешь на другом<br/>стенде, хитрец!";
                break;

            case CantPlayReason.FinishedPrizesNotGot:
                mainText.text = "Забирай свои призы<br/>и не приходи сюда!";
                break;

            case CantPlayReason.FinishedPrizesGot:
                mainText.text = "Вы забрали призы. Удачи!";
                break;
            }

            cantPlayHandler();
        }
    }

    Connections
    {
        target:server;

        onServerGlobalError:
        {

        }

        onServerRequestError:
        {

        }
    }



    function start()
    {
        visible = true;
        intro.animComplete();
        videoHolder.start();
        helloBlock.start();
    }

    function stop()
    {
        visible = false;
        videoHolder.stop();
        helloBlock.stop();
    }

    function setTestState(state)
    {
        reset();
    }

    function cantPlayHandler()
    {
        startBtn.visible = false;
        addText.visible = false;
    }
}
