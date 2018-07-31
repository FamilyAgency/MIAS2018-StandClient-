import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import com.app 1.0
import "../.."

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
                userData.clearBaseUserData();
                server.createUserRequest(tools.randomName(), tools.randomName(), tools.randomEmail(), tools.randomPhone());
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
                userData.clearBaseUserData();
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

    Tools
    {
        id:tools;
    }

    Connections
    {
        target: server;
        onBaseUserDataRecived:
        {
            userId.value = baseUserData.id;
        }
    }
}
