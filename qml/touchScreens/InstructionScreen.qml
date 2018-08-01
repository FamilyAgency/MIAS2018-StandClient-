import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8

Item
{
    id:instruction;

    anchors.fill: parent;

    property string mainTitleDefault: "НАДЕНЬТЕ<br/>УСТРОЙСТВО";
    property string addTitleDefault: "ИЛИ ОБРАТИТЕСЬ ЗА ПОМОЩЬЮ<br/>К ПРОМО-ПЕРСОНАЛУ";
    property string buttonText: "ПОГНАЛИ";

    signal animComplete();
    signal animStart();

//    Text
//    {
//        visible:false;
//        id: mainText;
//        text: mainTitleDefault;
//        font.family: "Helvetica";
//        font.pixelSize: 45;
//        color: "#ffffff";
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.verticalCenter:  parent.verticalCenter;
//        anchors.verticalCenterOffset: -200;
//        horizontalAlignment: Text.AlignHCenter;
//        verticalAlignment: Text.AlignVCenter;
//    }

//    Text
//    {
//        visible:false;
//        id: addText;
//        text: addTitleDefault;
//        font.family: "Helvetica";
//        font.pixelSize: 25;
//        color: "#ffffff";
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.top: mainText.bottom;
//        anchors.topMargin: 20;
//        horizontalAlignment: Text.AlignHCenter;
//        verticalAlignment: Text.AlignVCenter;
//    }

//    RowLayout
//    {
//        id:mindWave;
//        visible:false;

//        spacing: 6;
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.top: addText.bottom;
//        anchors.topMargin: 100;

//        Text
//        {
//            text: "signalLevel";
//            font.family: "Helvetica";
//            font.pixelSize: 15;
//            color: "#009900";
//        }

//        ProgressBar
//        {
//            id: signalProgressBar;
//            opacity: 1.;
//            value: mind.poorSignalLevel / 100.;

//            background: Rectangle
//            {
//                radius: 2;
//                color: "lightgray";
//                border.color: "gray";
//                border.width: 1;
//                implicitWidth: 300;
//                //implicitHeight: 24;
//            }

//            //            contentItem: Rectangle
//            //            {
//            //                color: "#009900";
//            //            }
//        }

//        PropertyAnimation
//        {
//            id: signalAnim;
//            target: signalProgressBar;
//            property: "value";
//            to: 100;
//            duration: 500;
//        }
//    }

//    Button
//    {
//        id: startBtn;
//        visible:false;
//        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.top: mindWave.bottom;
//        anchors.topMargin: 100;

//        contentItem: Text
//        {
//            text: buttonText;
//            font.family: "Helvetica";
//            font.pixelSize: 25;
//            color: "#ffffff"
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//        }
//        background: Rectangle
//        {
//            implicitHeight: 100;
//            implicitWidth: 280;
//            color:  startBtn.down ? "#3c2755" : "#801bfc";
//            radius: 10;
//        }

//        onClicked:
//        {
//            instructionModule.rouletteButtonClick();
//        }
//    }

    Video
    {
        id: video1;
        width: parent.width;
        height: parent.height;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;
    }


//    OpacityAnimator on opacity
//    {
//        id:opacityAnim;
//        from: 0;
//        to: 1;
//        duration: 1000;
//        running:false;

//        onRunningChanged:
//        {
//            if (!opacityAnim.running)
//            {
//                instruction.animComplete();
//            }
//        }
//    }
    Component.onCompleted:
    {
        video1.source = configController.getFileInAppDir("content/video/instruction.mp4");
    }

    Connections
    {
        target:mind;

        onAttentionChanged:
        {

        }

        onMeditationChanged:
        {

        }

        onPoorSignalLevelChanged:
        {
            // signalProgressBarColor.color = mind.poorSignalColor();
        }
    }

    function start()
    {
        console.log("start!!!!!!!!!!!!!!!!!!!!!!!")
       // opacity = 0;
        visible = true;
      //  opacityAnim.start();
        video1.seek(0);
        video1.play();
    }

    function stop()
    {
        video1.pause();
        visible = false;
    }
}
