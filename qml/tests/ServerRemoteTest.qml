import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

import com.app 1.0
import "../tools"
import "../mainScreens"

Item
{
    id: serverTest;

    Consts
    {
        id:consts;
    }

    Text
    {
        text: "===================TESTS===================";
        font.family: "Helvetica";
        font.pixelSize: 18;
        color: "#990000";

    }

    ColumnLayout
    {
        spacing: 10;
        y: 50;

        ScrollView
        {
            implicitWidth: 500;
            implicitHeight: 200;

            TextArea
            {
                id: ouputConsole;
                width: 310;
                height: 200;
                wrapMode: TextEdit.Wrap;
                selectByMouse: true;
                clip: true;
                textFormat: Text.RichText;
                font.family: "Helvetica";
                font.pixelSize: 14;
            }
        }

        Text
        {
            text: "Server Remote Tests";
            font.family: "Helvetica";
            font.pixelSize: 17;
            color: consts.infoTextColor;
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "Config Request";
                onClicked:
                {
                    server.configRequest(1);
                }
            }

            Button
            {
                text: "Update Request";
                onClicked:
                {
                    server.updatesRequest(1);
                }
            }

            Button
            {
                text: "Health Log Request";
                onClicked:
                {
                    server.healthLogRequest(1);
                }
            }
        }
        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "All Users Request";
                onClicked:
                {
                    server.allUsersRequest();
                }
            }

            Button
            {
                id: deleteBtn;
                text: "Delete All Test Users Request";
                onClicked:
                {
                    server.deleteAllTestUsersRequest();
                }
                background: Rectangle
                {
                    color: deleteBtn.hovered ?  "skyblue" : "#990000";
                    border.color: "#26282a";
                    border.width: 1;
                    radius: 4;

                    layer.enabled: true;
                    layer.effect: DropShadow
                    {
                        verticalOffset: 1;
                        color: "#aaaaaa";
                        samples: 4;
                        spread: 0.5;
                    }
                }
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "Server error";
                onClicked:
                {
                    server.simulateServerError();
                }
            }

            Button
            {
                text: "Server timeout";
                onClicked:
                {
                    server.simulateServerTimeout();
                }
            }
        }

        Button
        {
            text: "LOG OUT";
            id: logOutBtn;

            onClicked:
            {
                server.logout();
            }

            background: Rectangle
            {
                color: logOutBtn.hovered ?  "skyblue" : "#990000";
                border.color: "#26282a";
                border.width: 1;
                radius: 4;

                layer.enabled: true;
                layer.effect: DropShadow
                {
                    verticalOffset: 1;
                    color: "#aaaaaa";
                    samples: 4;
                    spread: 0.5;
                }
            }
        }

        Text
        {
            text: "Registration Tests";
            font.family: "Helvetica";
            font.pixelSize: 14;
            color: consts.infoTextColor;
        }

        Button
        {
            text: "Create User Request"
            onClicked:
            {
                userData.clearBaseUserData();
                server.createUserRequest(tools.randomName(), tools.randomName(), tools.randomEmail(), tools.randomPhone(), "M");
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "Search User Request";
                onClicked:
                {
                    userData.clearBaseUserData();
                    server.searchUserRequest(email.text, phone.text);
                }
            }

            TextField
            {
                id: email;
                implicitWidth: 160;
                placeholderText: "email@mail.com";
                text: "яндекс@почта.рф";
            }

            TextField
            {
                id: phone;
                implicitWidth: 160;
                placeholderText: "phone";
                text: "+79067706666";
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "Search User By Id Request";
                onClicked:
                {
                    userData.clearBaseUserData();
                    server.searchUserByIdRequest(userId.value);
                }
            }

            SpinBox
            {
                id: userId;
                value: 0;
                editable: true;
                from:0;
                to:3000;
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text:"Verify User Request";
                onClicked:
                {
                    server.verifyUserRequest(userVerifyId.value);
                }
            }

            SpinBox
            {
                id: userVerifyId;
                value: 0;
                editable: true;
                from: 0;
                to: 3000;
            }
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text: "Confirm User Request";

                onClicked:
                {
                    server.confirmUserRequest(userConfirmId.value, pinCode.value);
                }
            }

            SpinBox
            {
                id: userConfirmId;
                value: 0;
                editable: true;
                from :0;
                to: 3000;
            }

            SpinBox
            {
                id: pinCode;
                value: 0;
                editable: true;
                from: 0;
                to: 99999;
            }
        }

        Text
        {
            text: "Game Pass Tests";
            font.family: "Helvetica";
            font.pixelSize: 14;
            color: consts.infoTextColor;
        }

        RowLayout
        {
            spacing: 10;

            SpinBox
            {
                id: userGameId;
                value: 0;
                editable: true;
                from :0;
                to: 3000;
            }

            Button
            {
                text:"Start";

                onClicked:
                {
                    server.startGameRequest(userGameId.value);
                }
            }

            Button
            {
                text:"Update";

                onClicked:
                {
                    server.updateGameRequest(userGameId.value);
                }
            }

            Button
            {
                text:"Finish";

                onClicked:
                {
                    server.finishGameRequest(userGameId.value);
                }
            }
        }

        Text
        {
            text: "Prize Tests";
            font.family: "Helvetica";
            font.pixelSize: 14;
            color: consts.infoTextColor;
        }

        RowLayout
        {
            spacing: 10;

            Button
            {
                text:"Confirm Prize";

                onClicked:
                {
                    server.confirmPrizeRequest(userPrizeId.value, prizeId.value);
                }
            }

            SpinBox
            {
                id: userPrizeId;
                value: 0;
                editable: true;
                from :0;
                to: 3000;
            }


            SpinBox
            {
                id: prizeId;
                value: 1;
                editable: true;
                from :1;
                to: 2;
            }

            Button
            {
                text:"Go to game";
                onClicked:
                {
                     appController.setAppStateTest(AppState.Game);
                }
            }
        }
    }

    Tools
    {
        id:tools;
    }

    Connections
    {
        target: server;    

        onUserNotFound:
        {
            console.log("onUserNotFound");
        }

        onServerLogged:
        {
            ouputConsole.text = log;
        }        

        onBaseUserDataRecived:
        {
           // userGameId.value = baseUserData.id;
           // server.startGameRequest(userGameId.value);
           // appController.setTestUserId(userGameId.value);
        }

        onServerRequestSuccess:
        {
            console.log(" ========= onServerRequestSuccess =========");

            switch(responseType)
            {
            case ResponseType.CreateUserRequest:                
                console.log("ResponseType.CreateUserRequest");
                break;

            case ResponseType.SearchUserRequest:
                console.log("ResponseType.SearchUserRequest");
                break;

            case ResponseType.VerifyUserRequest:
                console.log("ResponseType.VerifyUserRequest");
                break;

            case ResponseType.ConfirmUserRequest:
                console.log("ResponseType.ConfirmUserRequest");
                break;

            case ResponseType.ConfirmPrizeRequest:
                console.log("ResponseType.ConfirmPrizeRequest");
                break;
            }

            console.log(" ==================");
        }

        onServerRequestError:
        {
            console.log(" ========= onServerRequestError =========");

            switch(responseType)
            {
            case ResponseType.CreateUserRequest:
                console.log("ResponseType.CreateUserRequest");
                break;

            case ResponseType.SearchUserRequest:
                console.log("ResponseType.SearchUserRequest");
                break;

            case ResponseType.VerifyUserRequest:
                console.log("ResponseType.VerifyUserRequest");
                break;

            case ResponseType.ConfirmUserRequest:
                console.log("ResponseType.ConfirmUserRequest");
                break;

            case ResponseType.ConfirmPrizeRequest:
                console.log("ResponseType.ConfirmPrizeRequest");
                break;
            }

            console.log(" ==================");
        }

        onServerGlobalError:
        {
            console.log(globalErrorType);
            switch(globalErrorType)
            {
            case ServerGlobalErrorType.TimeOut:
                console.log("ServerGlobalErrorType.TimeOut");
                break;

            case ServerGlobalErrorType.NetworkError:
                console.log("ServerGlobalErrorType.NetworkError");
                break;

            case ServerGlobalErrorType.Server500:
                console.log("ServerGlobalErrorType.Server500");
                break;
            }
        }
    }
}
