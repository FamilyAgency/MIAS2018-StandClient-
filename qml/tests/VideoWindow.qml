import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import QtMultimedia 5.8

Window
{
    objectName: "videoWindow";
    title: "videoWindow";
    visible: true;
    id: videoWindow;
    flags: Qt.Window;// standData.mainConfig.gameScreenIsSplash ? Qt.SplashScreen : Qt.Window;
    width: 540
    height: 960
    x: 0
    y: 0

    Video
    {
        id: player;
        anchors.fill: parent;
        anchors.centerIn: parent;
        fillMode: VideoOutput.PreserveAspectFit
        width: 1080;
        loops: MediaPlayer.Infinite;

        onStatusChanged: {
                if(status === MediaPlayer.Loaded)
                {
                    console.log("video loaded");
                }
            }
    }


    function setSource(source)
    {
        player.source = source;
        player.play();
    }
}
