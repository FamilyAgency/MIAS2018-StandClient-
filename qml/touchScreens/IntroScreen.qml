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
                wasError = false;
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
                cantPlayHandler("Вы можете начать игру заново,<br/>через " + userData.getSecondsToStart() + " секунд");
                break;

            case CantPlayReason.YouArePlaying:
                cantPlayHandler("Вы можете начать игру заново, через " + userData.getSecondsToStart());
                break;

            case CantPlayReason.FinishedPrizesNotGot:
                cantPlayHandler("Вы можете забрать свои призы<br/>на стойке выдачи призов!");
                break;

            case CantPlayReason.FinishedPrizesGot:
                cantPlayHandler("Вы прошли игру и забрали призы.<br/>Спасибо за участие!");
                break;
            }
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

    function cantPlayHandler(errorMsg)
    {
        wasError = true;
        videoHolder.startHelloState();
        helloBlock.startErrorState(errorMsg);
    }
}
