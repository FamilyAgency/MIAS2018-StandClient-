import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    id:backbtn

    Button
    {
        id: backBtn
        text:"back"
        visible:true
        onClicked:
        {
           appController.start();
        }
    }
}
