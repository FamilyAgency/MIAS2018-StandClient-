import QtQuick 2.0
import "results"

Item
{
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

    function stop()
    {

    }
}
