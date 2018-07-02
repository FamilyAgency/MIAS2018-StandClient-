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
                    loginModule.loginSuccessTest(stageBox.value);
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
                loginModule.userDoesntExist();
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
                    loginModule.finished(prizeBox.value);
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
                loginModule.playedRecently();
            }
        }

        Button
        {
            text:"You are playing!!!"
            onClicked:
            {
                loginModule.youArePlaying();
            }
        }

        Button
        {
            text:"Module error"
            onClicked:
            {
                loginModule.moduleError();
            }
        }

        Button
        {
            text:"LOG OUT"
            id:logOutBtn
            onClicked:
            {
                loginModule.logoutTest();
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
