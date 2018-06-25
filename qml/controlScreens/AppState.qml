import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    Connections
    {
        target:appController;
        onAppStateChanged:
        {
            curScreen.text = "Current screen: " + appState;
        }
    }

    ColumnLayout
    {
        spacing: 10;
        Text
        {            
            text: "App state" ;
            font.family: "Helvetica"
            font.pixelSize: 17
            color: "#000099"
        }

        Text
        {
            id:curScreen;
            text: "Current screen: ";
            font.family: "Helvetica"
            font.pixelSize: 15
            color: "#999999"
        }
    }
}
