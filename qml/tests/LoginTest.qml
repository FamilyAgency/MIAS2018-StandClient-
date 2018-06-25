import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

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

        Button
        {
            text:"Login success / first time"
            onClicked:
            {
                loginModule.loginSuccessTest();
            }
        }

        Button
        {
            text:"Login success / second time"
            onClicked:
            {

            }
        }

        Button
        {
            text:"Wait you played resent"
            onClicked:
            {

            }
        }

        Button
        {
            text:"User doesn't exist"
            onClicked:
            {

            }
        }

        Button
        {
            text:"Module error"
            onClicked:
            {

            }
        }

        Button
        {
            text:"Log out"
            onClicked:
            {
                loginModule.logoutTest();
            }
        }
    }
}
