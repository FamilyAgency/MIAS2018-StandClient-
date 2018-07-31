import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

import "../components"
import com.app 1.0

Window
{
    title: "User Window";
    x: 0;
    y: 0;
    width: 400;
    height: 600;
    visible: true;
    flags: Qt.SplashScreen;

    Item
    {
        x: 50;
        y: 50;

        ColumnLayout
        {
            spacing: 15;

            ColumnLayout
            {
                spacing: 10;

                Text
                {
                    text: "User data";
                    font.family: "Helvetica";
                    font.pixelSize: 17;
                    color: "#000099";
                }

                Text
                {
                    text: "Id: " + userData.baseUserData.id;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Name: " + userData.baseUserData.name;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Surname: " + userData.baseUserData.surname;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Email: " + userData.baseUserData.email;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Phone: " + userData.baseUserData.phone;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Confirmed pin: " + userData.baseUserData.isPinConfirmed();
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "Is test user: " + userData.baseUserData.test;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    id:pinToConfirmed;
                    text: "Pin to confirmed: ";
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }
            }

            ColumnLayout
            {
                spacing: 10;
                Text
                {
                    text: "Prizes data";
                    font.family: "Helvetica";
                    font.pixelSize: 17;
                    color: "#000099";
                }

                Text
                {
                    text: "prize1: " + userData.prizesUserData.prize1;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "prize2: " + userData.prizesUserData.prize2;
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }
            }

            ColumnLayout
            {
                spacing: 10;
                Text
                {
                    text: "Game data";
                    font.family: "Helvetica";
                    font.pixelSize: 17;
                    color: "#000099";
                }

                Text
                {
                    text: "stage1: " + userData.gameUserData.stageTimes[0].toFixed(1);
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "stage2: " + userData.gameUserData.stageTimes[1].toFixed(1);
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "stage3: " + userData.gameUserData.stageTimes[2].toFixed(1);
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#999999";
                }

                Text
                {
                    text: "super game: " + userData.gameUserData.superGameTime.toFixed(1);
                    font.family: "Helvetica";
                    font.pixelSize: 15;
                    color: "#990000";
                }
            }
        }
    }
}
