import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.2
import com.app 1.0

Item
{
    id:intro;

    property string mainTitleDefault: "УПРАВЛЯЙ<br/>SANTA FE<br/>СИЛОЙ МЫСЛИ";
    property string addTitleDefault: "ПОЖАЛУЙСТА,<br/>ПРИЛОЖИТЕ БРАСЛЕТ";
    property string addTitleHelloText: "ПОЗНАКОМЬСЯ С УВЛЕКАТЕЛЬНЫМ,<br/>МИРОМ SANTA FE!<br/>ПРЕДСТАВЛЯЕШЬ,\
 УПРАВЛЯТЬ<br/>АВТОМОБИЛЕМ SANTA FE СТАЛО<br/>ВОЗМОЖНО СИЛОЙ МЫСЛИ";
    property string buttonText: "НАЧНЕМ?";

    signal animComplete();
    signal animStart();

    anchors.fill: parent;
    anchors.centerIn: parent;

    Text
    {
        x: 50;
        y: 50;
        id:versionText;
        Layout.alignment : Qt.AlignHCenter;
        text: "Version: " + standData.mainConfig.version;
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#888888";
    }

    Text
    {
        x: 50;
        y: 80;
        id:memoryText;
        Layout.alignment : Qt.AlignHCenter;
        text: "Memory: " + monitoring.memory + " MB";
        font.family: "Helvetica";
        font.pixelSize: 20;
        color: "#888888";
    }

    ColumnLayout
    {
        spacing: 10;
        anchors.centerIn: parent;

        Text
        {
            id:mainText;
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
            id:addText;
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
                color: "#ffffff"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle
            {
                implicitHeight: 100;
                implicitWidth: 280;
                color:  startBtn.down ? "#3c2755" : "#801bfc";
                radius: 10;
            }

            onClicked:
            {
                appController.startInstruction();
            }
        }
    }

    Connections
    {
        target:introModule;

        onUserStartPlay:
        {
            intro.animStart();
            opacity = 0;
            opacityAnim.start();

            mainText.text = "ПРИВЕТ,<br/>" + userData.baseUserData.name;
            mainText.visible = true;
            addText.visible = true;
            addText.text = addTitleHelloText;
            startBtn.visible = true;
        }

        onUserNotFound:
        {
            mainText.text = "Похоже, что тебя<br/>не существует!";
            cantPlayHandler();
        }
    }

    Connections
    {
        target:userData;

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

            case CantPlayReason.Finished:
                mainText.text = "Забирай свои призы<br/>и не приходи сюда!";
                break;
            }

            cantPlayHandler();
        }
    }

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
    }

    function stop()
    {
        visible = false;

        mainText.text =  mainTitleDefault;
        addText.text =  addTitleDefault;

        mainText.visible = true;
        addText.visible = true;
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
