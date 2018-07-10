import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../mainScreens"

Item {
    id: loginTest

    Consts
    {
        id:consts;
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {
            text: "Server Login Test";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: consts.infoTextColor
        }

        RowLayout
        {
            spacing: 10;
            Button
            {
                text:"Login success | stage : "
                onClicked:
                {
                    server.fetchUserWithGameId(idBox.value, stageBox.value);
                }
            }

            SpinBox
            {
                id: idBox
                value: 1000
                editable: true
                from:1000
                to:3000
            }

            SpinBox
            {
                id: stageBox
                value: 1
                editable: true
                from:1
                to:3
            }
        }

        Button
        {
            text:"User doesn't exist"
            onClicked:
            {
                server.fetchDoesntExistUser(-1);
            }
        }

        RowLayout
        {
            spacing: 10;
            Button
            {
                text:"Finished | prizes get: "
                onClicked:
                {
                    server.finishedWithPrizes(prizeBox.value);
                }
            }

            SpinBox
            {
                id: prizeBox
                value: 0
                editable: true
                from:0
                to:2
            }
        }

        Button
        {
            text:"Wait you played recent"
            onClicked:
            {
                server.fetchPlayedRecentUser(100);
            }
        }

        Button
        {
            text:"You are playing!!!"
            onClicked:
            {
                server.fetchAlreadyPlayingUser(200);
            }
        }

        Button
        {
            text:"Server error"
            onClicked:
            {
                server.simulateServerError();
            }
        }

        Button
        {
            text:"Server timeout"
            onClicked:
            {
                server.simulateServerTimeout();
            }
        }

        Button
        {
            text:"LOG OUT"
            id:logOutBtn
            onClicked:
            {
                server.logout();
            }
            background: Rectangle
            {
                color: logOutBtn.hovered ?  'skyblue' : "#990000";
                border.color: "#26282a"
                border.width: 1
                radius: 4

                layer.enabled: true
                layer.effect: DropShadow
                {
                    verticalOffset: 1
                    color: "#aaaaaa"
                    samples:4
                    spread: 0.5
                }
            }
        }        
    }
}
