import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item
{
    id:instruction
    anchors.fill: parent


    Rectangle
    {
        anchors.fill: parent
        color: "white"
        width: 400;
        height: 400;
        Text
        {
            id:mainText3;
            anchors.centerIn: parent
            text: "Наденьте устройство или обратитесь к врачу";
            font.family: "Helvetica"
            font.pixelSize: 25
            color: "#999999"
        }

        RowLayout
        {
            spacing: 6;
           // anchors.centerIn: parent
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: mainText3.bottom;
            anchors.topMargin: 50;
            Text
            {
                text: "signalLevel";
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#009900"
            }
            ProgressBar
            {
                id:signalProgressBar;
                opacity:0.2
                value: mind.poorSignalLevel / 100.;
                style: ProgressBarStyle
                {
                    background: Rectangle
                    {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 300
                        implicitHeight: 24
                    }

                    progress: Rectangle
                    {
                      //id:signalProgressBarColor;
                        color:  "#009900"
                        border.color: "steelblue"
                    }
                }
            }

            PropertyAnimation
            {
                id: signalAnim;
                target: signalProgressBar;
                property: "value";
                to: 100;
                duration: 500
            }
        }

        Button
        {
            text: "StartGame";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: mainText3.bottom;
            anchors.topMargin: 100;
            onClicked:
            {
                appController.startRoulette();
            }
        }
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

    function stop()
    {
      //  swipeView.currentIndex = 0;
    }

//    SwipeView {
//        id: swipeView;

//        currentIndex: 0
//        anchors.fill: parent
//        Rectangle
//        {
//            color: "white"
//            width: 400;
//            height: 400;
//            Text
//            {
//                id:mainText;
//                anchors.centerIn: parent
//                text: "Инструкция1";
//                font.family: "Helvetica"
//                font.pixelSize: 25
//                color: "#999999"
//            }
//        }

//        Rectangle
//        {
//            color: "white"
//            width: 400;
//            height: 400;
//            Text
//            {
//                id:mainText2;
//                anchors.centerIn: parent
//                text: "Инструкция2";
//                font.family: "Helvetica"
//                font.pixelSize: 25
//                color: "#999999"
//            }
//        }

//        Rectangle
//        {
//            color: "white"
//            width: 400;
//            height: 400;
//            Text
//            {
//                id:mainText3;
//                anchors.centerIn: parent
//                text: "Инструкция3";
//                font.family: "Helvetica"
//                font.pixelSize: 25
//                color: "#999999"
//            }

//            Button
//            {
//                text: "StartGame"
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.top: mainText3.bottom
//                onClicked:
//                {
//                    appController.startGame();
//                }
//            }
//        }
//    }

//    PageIndicator
//    {
//        id: indicator

//        count: swipeView.count
//        currentIndex: swipeView.currentIndex

//        anchors.bottom: swipeView.bottom
//        anchors.horizontalCenter: parent.horizontalCenter
//    }
}
