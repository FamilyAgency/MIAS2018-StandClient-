import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import QtMultimedia 5.8

import com.app 1.0

Item
{
    id:intro;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "УПРАВЛЯЙ<br/>SANTA FE<br/>СИЛОЙ МЫСЛИ";
    property string addTitleDefault: "ПОЖАЛУЙСТА,<br/>ПРИЛОЖИТЕ БРАСЛЕТ";
    property string addTitleHelloText: "ПОЗНАКОМЬСЯ С УВЛЕКАТЕЛЬНЫМ,<br/>МИРОМ SANTA FE!<br/>ПРЕДСТАВЛЯЕШЬ,\
 УПРАВЛЯТЬ<br/>АВТОМОБИЛЕМ SANTA FE СТАЛО<br/>ВОЗМОЖНО СИЛОЙ МЫСЛИ";
    property string buttonText: "НАЧНЕМ?";

    signal animComplete();
    signal animStart();

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

    Video
    {
        id: video2;
        width: parent.width;
        height: parent.height;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        focus: true;

        OpacityAnimator on opacity
        {
            id:opacityAnim;
            from: 0;
            to: 1;
            duration: 1000
            running:false;

            onRunningChanged:
            {
                if (!opacityAnim.running)
                {
                    intro.animComplete();
                }
            }
        }
    }

//    MediaPlayer {
//        id: mediaplayer
//        source:  configController.getFileInAppDir("content/video/redButton.avi");
//    }

//    VideoOutput {
//        anchors.fill: parent
//        source: mediaplayer
//        id: video;
//    }

//    ShaderEffect {
//        property variant source: ShaderEffectSource { sourceItem: video; hideSource: true }
//        property real wiggleAmount: 0.5
//        anchors.fill: video
//        //  visible:false;

//        fragmentShader: "
//                   varying highp vec2 qt_TexCoord0;
//                   uniform sampler2D source;
//                   uniform highp float wiggleAmount;
//                   void main(void)
//                   {

//lowp vec4 tex = texture2D(source, qt_TexCoord0);

//                         highp float rem = 1.0;
//                       if(tex.r == 0.0 && tex.g == 0.0 && tex.b == 0.0)
//                             rem = 0.0;

//                       gl_FragColor = tex *rem;
//                   }
//               "
//    }



    ColumnLayout
    {
        id: data;
        spacing: 10;
        anchors.centerIn: parent;
        opacity: 0;

        Text
        {
            id: mainText;
            text: mainTitleDefault;
            font.family: "Helvetica";
            font.pixelSize: 45;
            color: "#ffffff";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter:  parent.verticalCenter;
            anchors.verticalCenterOffset: -100;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            Layout.preferredWidth: 500;
            textFormat: Text.StyledText;
            elide: Text.ElideRight;
        }

        Text
        {
            id: addText;
            text: addTitleDefault;
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#ffffff";
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter:  parent.verticalCenter;
            anchors.verticalCenterOffset: 100;
            horizontalAlignment: Text.AlignHCenter;
        }

        Button
        {
            id: startBtn;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: addText.bottom;
            anchors.topMargin: 100;
            visible:false;
            contentItem: Text
            {
                text: buttonText;
                font.family: "Helvetica";
                font.pixelSize: 25;
                color: "#ffffff";
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
            }
            background: Rectangle
            {
                implicitHeight: 150;
                implicitWidth: 150;
                color: startBtn.down ? "#3c2755" : "#801bfc";
                radius: 100;
            }

            onClicked:
            {
                introModule.startButtonClick();
            }
        }

        OpacityAnimator on opacity
        {
            id:opacityAnim1;
            from: 0;
            to: 1;
            duration: 4000
            running:false;
        }
    }



    Component.onCompleted:
    {
        video1.source = configController.getFileInAppDir("content/video/intro1.mp4");
        video2.source = configController.getFileInAppDir("content/video/intro2.mp4");
       // buttonVideo.source = configController.getFileInAppDir("content/video/redButton.avi");
        //mediaplayer.play();

    }

    Timer
    {
        id: intro1;
        interval:1000;
        onTriggered:
        {
            video1.seek(0);
            video1.pause();
            opacityAnim1.start();

            mainText.text = "ПРИВЕТ,<br/>" + userData.baseUserData.name;
            mainText.visible = true;
            addText.visible = true;
            addText.text = addTitleHelloText;
            startBtn.visible = true;
        }
    }

    Connections
    {
        target:introModule;

        onUserStartPlay:
        {
            intro.animStart();
            video2.seek(0);
            video2.play();
            //buttonVideo.seek(0);
           // buttonVideo.play();
            video2.visible = true;
            video2.opacity = 0;
            opacityAnim.start();

            data.opacity = 0;
            intro1.start();
        }

        onUserNotFound:
        {
            mainText.text = "Похоже, что тебя<br/>не существует!";
            cantPlayHandler();
        }

        onUserCantStartReason:
        {
            console.log("cant start reason ::: ", userData.getReasonCantPlay(), reason);

            switch(reason)
            {
            case CantPlayReason.WasRecently:
                mainText.text = "Недавно же играл!";
                break;

            case CantPlayReason.YouArePlaying:
                mainText.text = "Играешь на другом<br/>стенде, хитрец!";
                break;

            case CantPlayReason.FinishedPrizesNotGot:
                mainText.text = "Забирай свои призы<br/>и не приходи сюда!";
                break;

            case CantPlayReason.FinishedPrizesGot:
                mainText.text = "Вы забрали призы. Удачи!";
                break;
            }

            cantPlayHandler();
        }
    }

    Connections
    {
        target:server;

        onServerGlobalError:
        {

        }

        onServerRequestError:
        {

        }
    }

    function start()
    {
        visible = true;
        intro.animComplete();


        video1.visible = true;
        video1.play();
    }

    function stop()
    {
        visible = false;

        video2.visible = false;
        video2.pause();

        video1.visible = false;
        video1.pause();

        mainText.text =  "";
        addText.text =  "";

        mainText.visible = true;
        //addText.visible = true;
        startBtn.visible = false;
    }

    function setTestState(state)
    {
        reset();
    }

    function cantPlayHandler()
    {
        startBtn.visible = false;
        addText.visible = false;
    }
}
