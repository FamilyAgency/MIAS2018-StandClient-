import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{
    id:login;

    anchors.fill: parent;
    anchors.centerIn: parent;

    ColumnLayout
    {
        spacing: 10;
        anchors.centerIn: parent;

        Text
        {
            id:mainText;
            Layout.alignment : Qt.AlignHCenter;
            text: "Рулетка";
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#999999";
        }
    }
}
