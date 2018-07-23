import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{
    anchors.fill: parent;
    anchors.centerIn: parent;
    RowLayout
    {
        spacing: 10;
        anchors.bottom: parent.bottom;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottomMargin: 100;

        Button
        {
            id: createBtn;
            text:"Create User Request";
            contentItem: Text
            {
                text:"Create User Request";
                color: "#000000"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle
            {
                implicitHeight: 50;
                implicitWidth: 20;
                color:  createBtn.down ? "#3c2755" : "#ffffff";
            }
            onClicked:
            {
                server.clearBaseUserInfo();
                server.createUserRequest("Юрий", "Попов", randomEmail(), "8" + randomPhone());
            }
        }

        Button
        {
            id: rfidBtn;
            text:"RFID Request";
            contentItem: Text
            {
                text:"RFID Request";
                color: "#000000"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle
            {
                implicitHeight: 50;
                implicitWidth: 20;
                color:  rfidBtn.down ? "#3c2755" : "#ffffff";
            }
            onClicked:
            {
                server.clearBaseUserInfo();
                server.searchUserByIdRequest(userId.value);
            }
        }

        SpinBox
        {
            id: userId;
            value: 325;
            editable: true;
            from:0;
            to:3000;
        }
    }

    Connections
    {
        target: server;
        onServerRequestSuccess:
        {
            if(responseType == ResponseType.CreateUserRequest)
            {
                userId.value = server.baseUserData.id;
            }
        }

    }

    function randomPhone()
    {
        return Math.random() * (9999999999 - 1111111111) + 1111111111;
    }

    function randomEmail()
    {
        var email = "";
        var text = "";
        var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

        for (var i = 0; i < 5; i++)
            text += possible.charAt(Math.floor(Math.random() * possible.length));

        email = text + "@";

        var text = "";
        for (var i = 0; i < 4; i++)
            text += possible.charAt(Math.floor(Math.random() * possible.length));

         email += text + ".com";

        return email;
    }
}
