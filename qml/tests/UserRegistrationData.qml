import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2
import "../components"
import com.app 1.0

Window
{
    objectName: "touchWindow";
    title: "User Window";
    visible: true;
    flags: Qt.SplashScreen;
    width: 400;
    height: 600;
    x: 0;
    y: 0;

    Connections
    {
        target: server;
        onBaseUserInfoChanged:
        {
            pinToConfirmed.text = "Pin to confirmed: " + server.baseUserInfo.getPinToConfirm();
        }
    }

    Item
    {
        x: 50;
        y: 50;

        ColumnLayout
        {
            spacing: 10;
            Text
            {
                text: "User data";
                font.family: "Helvetica"
                font.pixelSize: 17
                color: "#000099"
            }

            Text
            {
                text: "Id: " + server.baseUserInfo.id;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Name: " + server.baseUserInfo.name;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Surname: " + server.baseUserInfo.surname;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Email: " + server.baseUserInfo.email;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Phone: " + server.baseUserInfo.phone;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Confirmed pin: " + server.baseUserInfo.isPinConfirmed();
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                text: "Is test user: " + server.baseUserInfo.test;
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }

            Text
            {
                id:pinToConfirmed;
                text: "Pin to confirmed: ";
                font.family: "Helvetica"
                font.pixelSize: 15
                color: "#999999"
            }
        }
    }
}
