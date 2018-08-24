import QtQuick 2.0

import "../../tools"

Item
{
    Consts
    {
        id:consts;
    }

    Image
    {
        id: donate;
        source: "qrc:/resources/finish.png";
    }

    Image
    {
        id: flag;
       // visible: false;
        property int currentImage: 1
        x: 0
        y: 0
        source: configController.getFileInAppDir("content/misc/flag/" + currentImage + ".png");
        NumberAnimation on currentImage
        {
            from: 1;
            to: 72;
            duration: 71 * 1000. / consts.animFPS;
            running: true;
            loops: Animation.Infinite;
        }
    }

    function showFlag()
    {
        visible = true;
    }

    function hideFlag()
    {
        visible = false;
    }

    function setFlagPosition(x, y)
    {
        flag.x = x - 10;
        flag.y = y - 66;
        donate.x = x - 16;
        donate.y = y - 16;
    }

}
