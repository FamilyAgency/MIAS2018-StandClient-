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


        TextArea
        {
            id:ouputConsole;
            implicitWidth: 310;
            implicitHeight: 200;
            width: 310;
            height: 200;
            wrapMode: TextEdit.Wrap;
            selectByMouse: true;
            clip: true;
            textFormat: Text.RichText;
            font.family: "Helvetica";
            font.pixelSize: 14;
        }
        Text
        {
            text: "Server Remote Tests";
            font.family: "Helvetica"
            font.pixelSize: 17
            color: consts.infoTextColor
        }

        RowLayout
        {
            spacing: 10;



            Button
            {
                text:"Config Request"
                onClicked:
                {
                    server.configRequest(1);
                }
            }       
        }

        Button
        {
            text:"Update Request"
            onClicked:
            {
                server.updatesRequest(1);
            }
        }

        Button
        {
            text:"Health Log Request"
            onClicked:
            {
                server.healthLogRequest(1);
            }
        }

        Button
        {
            text:"All Users Request"
            onClicked:
            {
                server.allUsersRequest();
            }
        }

        Button
        {
            text:"Create User Request"
            onClicked:
            {
                server.createUserRequest(true);
            }
        }

        Button
        {
            text:"Search User Request"
            onClicked:
            {
                server.searchUserRequest("15@gmail.com", "");
            }
        }

        Button
        {
            text:"Delete All Test Users Request"
            onClicked:
            {
                server.deleteAllTestUsersRequest();
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text:"Verify User Request"
                onClicked:
                {
                    server.verifyUserRequest(userVerifyId.value);
                }
            }

            SpinBox
            {
                id: userVerifyId
                value: 0
                editable: true
                from:0
                to:3000
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text:"Confirm User Request"
                onClicked:
                {
                    server.confirmUserRequest(userConfirmId.value, pinCode.value);
                }
            }

            SpinBox
            {
                id: userConfirmId
                value: 0
                editable: true
                from:0
                to:3000
            }

            SpinBox
            {
                id: pinCode
                value: 0
                editable: true
                from:0
                to:99999
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
