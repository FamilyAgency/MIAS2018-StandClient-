import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

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
            text:"RFID Request";
            onClicked:
            {
                server.clearBaseUserInfo();
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
}
