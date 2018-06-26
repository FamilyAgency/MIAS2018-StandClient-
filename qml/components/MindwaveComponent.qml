import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:root;

    property double nextAttentionValue: 0.0;
    property double nextMeditationValue: 0.0;
    property double alphaInvis: 0.2;

    Connections
    {
        target:mind;
        onAttentionChanged:
        {
            nextAttentionValue = mind.attention / 100.0;
            attentionAnim.to = nextAttentionValue;
            attentionAnim.duration = 1000;
            attentionAnim.start();
        }

        onMeditationChanged:
        {
            nextMeditationValue = mind.meditation / 100.0;
            meditationAnim.to = nextMeditationValue;
            meditationAnim.duration = 1000;
            meditationAnim.start();
        }

        onPoorSignalLevelChanged:
        {
            console.log("mind.poorSignalColor()  ", mind.poorSignalColor());
            signalLevel.color = mind.poorSignalColor();
        }
    }

    ColumnLayout
    {

        spacing: 10;
        RowLayout {
            spacing: 6;
            Text {
                text: "Mindwave component";
                font.family: "Helvetica"
                font.pixelSize: 17
                color: "#009900"
            }
        }

        Text
        {
            id:conServer;
            text: "Server: " + mind.config.ip;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:conPort;
            text: "Port: " + mind.config.port;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:auto;
            text: "Auto connection: " + mind.config.autoConnect;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text
        {
            id:conStatus;
            text: "Connection status: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        Text {
            id:signalLevel
            text: "Signal level: " + mind.poorSignalLevel;
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }

        RowLayout {
            spacing: 6;


            Text {
                text: "Attention";
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#990000"
            }
            //spacing: 6;
            ProgressBar
            {
                id:attentionProgressBar;
                opacity:0.2
                value: 0.0;
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 300
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color:  "#990000"
                        border.color: "steelblue"
                    }
                }
            }

            PropertyAnimation
            {
                id: attentionAnim;
                target: attentionProgressBar;
                property: "value";
                to: 100;
                duration: 500
            }
        }

        RowLayout
        {
            visible: true
            opacity: 0.2;
            Text {
                text: "Meditation";
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#000099"
            }
            spacing: 6;
            ProgressBar
            {
                id:meditationProgressBar;
                value: 0.0
                style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "lightgray"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 300
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color: "#000099"
                        border.color: "steelblue"
                    }
                }
            }
            PropertyAnimation
            {
                id: meditationAnim;
                target: meditationProgressBar;
                property: "value";
                to: 100;
                duration: 500
            }
        }

        RowLayout
        {
            visible: false
            spacing: 6;
            ExclusiveGroup { id: tabPositionGroup }
            RadioButton {
                id: btn1
                text: "Attention"
                checked: true
                exclusiveGroup: tabPositionGroup
                onCheckedChanged:
                {
                    core.gameStrategy = btn1.checked ? 1 : 2;
                }
            }

            RadioButton {
                id: btn2
                text: "Meditation"
                checked: false
                exclusiveGroup: tabPositionGroup
            }

        }
    }
}
