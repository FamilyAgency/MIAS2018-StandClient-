import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2

import com.app 1.0
import "intro"
import "../tools"

Item
{
    id:intro;
    anchors.fill: parent;
    anchors.centerIn: parent;

    property bool wasError: false;

    signal animComplete();
    signal animStart();

    Tools
    {
        id: tools;
    }

    IntroTitles
    {
        id: introTitiles;
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
            helloBlock.startHelloState();
            introTitiles.hide();
        }

        onUserNotFound:
        {
            cantPlayHandler("Похоже, что вас<br/>не существует!<br/><br/> Обратитесь за помощью <br/>к промо-персоналу.");
        }

        onUserCantStartReason:
        {
            console.log("cant start reason ::: ", userData.getReasonCantPlay(), reason);

            switch(reason)
            {
            case CantPlayReason.WasRecently:
            case CantPlayReason.YouArePlaying:
                var seconds = userData.getSecondsToStart();
                cantPlayHandler("Попробуйте снова <br/>через " + tools.getTimeToStart(seconds)+ ".<br/>Вам обязательно повезет");
                break;

            case CantPlayReason.FinishedPrizesNotGot:
                cantPlayHandler("Получите ваш<br/> прохладительный напиток<br/>у стойки выдачи подарков.");
                break;

            case CantPlayReason.FinishedPrizesGot:
                cantPlayHandler("Вы уже получили<br/> прохладительный напиток.<br/>Спасибо за участие!");
                break;
            }
        }
    }

    Connections
    {
        target:rfid;

        onCardReaderError:
        {
            switch(error)
            {
            case CardReaderError.CardParsing:
                cantPlayHandler("Похоже, что вас<br/>не существует!<br/><br/> Обратитесь за помощью <br/>к промо-персоналу.");
                break;
            }
        }
    }

    function start()
    {
        visible = true;
        intro.animComplete();
        helloBlock.start();
        introTitiles.show();
    }

    function stop()
    {
        visible = false;
        helloBlock.stop();
    }

    function cantPlayHandler(errorMsg)
    {
        introTitiles.hide();
        wasError = true;
        helloBlock.startErrorState(errorMsg);
    }
}
