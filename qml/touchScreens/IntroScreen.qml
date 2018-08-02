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

    property bool wasError: false;

    signal animComplete();
    signal animStart();

    VideoHolder
    {
        id: videoHolder;
    }

    HelloBlock
    {
        id: helloBlock;

        onAnimStart:
        {
            intro.animStart();
        }

        onInAnimComplete:
        {
            intro.animComplete();
        }

        onOutAnimComplete:
        {
            intro.animComplete();

            if(wasError)
            {
                appController.backToIntro();
            }
            else
            {
                introModule.startButtonClick();
            }
        }
    }

    Connections
    {
        target:introModule;

        onUserStartPlay:
        {
            wasError = false;
            videoHolder.startHelloState();
            helloBlock.startHelloState();
        }

        onUserNotFound:
        {
            cantPlayHandler("Похоже, что тебя<br/>не существует!");
        }

        onUserCantStartReason:
        {
            console.log("cant start reason ::: ", userData.getReasonCantPlay(), reason);

            switch(reason)
            {
            case CantPlayReason.WasRecently:
                cantPlayHandler("Недавно же играл!");
                break;

            case CantPlayReason.YouArePlaying:
                cantPlayHandler("Играешь на другом<br/>стенде, хитрец!");
                break;

            case CantPlayReason.FinishedPrizesNotGot:
                cantPlayHandler("Забирай свои призы<br/>и не приходи сюда!");
                break;

            case CantPlayReason.FinishedPrizesGot:
                cantPlayHandler("Вы забрали призы. Удачи!");
                break;
            }
        }
    }

    Connections
    {
        target:server;

        onServerGlobalError:
        {
            cantPlayHandler("Что-то пошло не так!<br/>Обратитесь к промоутеру.");
        }

        onServerRequestError:
        {
            cantPlayHandler("Что-то пошло не так!<br/>Обратитесь к промоутеру.");
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

    function cantPlayHandler(errorMsg)
    {
        wasError = true;
        videoHolder.startHelloState();
        helloBlock.startErrorState(errorMsg);
    }
}
