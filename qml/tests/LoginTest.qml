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
            text: "Login Test";
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
                    introModule.loginSuccessTest(stageBox.value);
                }
            }

            SpinBox
            {
                id: stageBox
                value: 1
                editable: true
            }
        }

        Button
        {
            text:"User doesn't exist"
            onClicked:
            {
                introModule.userDoesntExist();
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
                    introModule.finished(prizeBox.value);
                }
            }

            SpinBox
            {
                id: prizeBox
                value: 0
                editable: true
            }
        }

        Button
        {
            text:"Wait you played resent"
            onClicked:
            {
                introModule.playedRecently();
            }
        }

        Button
        {
            text:"You are playing!!!"
            onClicked:
            {
                introModule.youArePlaying();
            }
        }

        Button
        {
            text:"Module error"
            onClicked:
            {
                introModule.moduleError();
            }
        }

        Button
        {
            text:"LOG OUT"
            id:logOutBtn
            onClicked:
            {
                introModule.logoutTest();
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

        RowLayout
        {
            spacing: 10;
            Button
            {
                text:"RFID entered: "
                onClicked:
                {
                    introModule.rfidRecieved(rfidBox.value);
                }
            }

            SpinBox
            {
                id: rfidBox
                value: 1000
                from: 0
                to: 2000
                editable: true
            }
        }
    }
}
