import QtQuick 2.0
import "results"

Item
{
    id: gameResultScreen;

    signal animComplete();
    signal animStart();

    anchors.fill: parent;

    GameResultFirstTime
    {
        id:gameResultFirstTime;

        onStartSuperGame:
        {
            appController.startSuperGame();
        }

        onGetColaCan:
        {
            appController.backToIntro();
        }
    }

    function start()
    {
        visible = true;
        gameResultScreen.animComplete();
    }

    function stop()
    {
        visible = false;
    }
}
