import QtQuick 2.0
import "../../tools"

Text
{
    id: counter;

    property var countText: [ "3", "2", "1"];

    signal animationCompelete();

    text: countText[0];
    font.family: font.hyundaiSansHeadMedium;
    font.pixelSize: 300 * consts.designScale;
    color: "white";
    verticalAlignment: Text.AlignVCenter;
    horizontalAlignment: Text.AlignHCenter;
    anchors.fill: parent;
    anchors.bottom: parent.bottom;

    FontManager
    {
        id: font;
    }

    SequentialAnimation
    {
        id: animator;

        property int currentLoop: 0;

        onStarted:
        {
            //currentLoop = 0;
        }

        onStopped:
        {
            currentLoop++;
            if(currentLoop < countText.length)
            {
                counter.text = countText[currentLoop];
                animator.restart();
            }
            else
            {
                hide();
                counter.animationCompelete();
            }
        }

        ParallelAnimation
        {
            NumberAnimation { target: counter; property: "scale";   from: 0; to: 1; duration: 500 }
            NumberAnimation { target: counter; property: "opacity"; from: 0; to: 1; duration: 500 }
        }

        ParallelAnimation
        {
            NumberAnimation { target: counter; property: "scale";   from: 1; to: 2; duration: 500 }
            NumberAnimation { target: counter; property: "opacity"; from: 1; to: 0; duration: 500 }
        }
    }

    Component.onCompleted:
    {
        animator.restart();
    }

    function show()
    {
        counter.text = countText[0];
        counter.visible = true;
        animator.currentLoop = 0;
        animator.restart();
    }

    function hide()
    {
        animator.stop();
        counter.visible = false;
    }
}
