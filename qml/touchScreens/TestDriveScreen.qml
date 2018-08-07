import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item
{
    id: testDrive;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "ТЕСТ ДРАЙВ";

    signal animComplete();
    signal animStart();

    Text
    {
        id: mainText;
        anchors.top: parent.top;
        anchors.topMargin: 100;
        anchors.horizontalCenter: parent.horizontalCenter;
        text: mainTitleDefault;
        font.family: "Helvetica";
        font.pixelSize: 55;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;
    }

    ColumnLayout
    {
        spacing: 100;

        y:200;
        x:20;

//        Button
//        {
//            text:"Get Dealers";

//            onClicked:
//            {
//                server.getDealersRequest();
//            }
//        }

//        Button
//        {
//            text:"Test Drive";

//            onClicked:
//            {
//                server.testDriveRequest(1, 1);
//            }
//        }

        ComboBox
        {
            currentIndex: 0
            model:ListModel
            {
                id: cityModel
            }
            implicitWidth: 500;

            onCurrentIndexChanged:
            {
                calculateDilers(currentIndex);
            }
        }

        ComboBox
        {
            currentIndex: 0
            model:ListModel
            {
                id: dilersModel
            }
            implicitWidth: 500;
            id: dilersCombo;
        }
    }

     property var dilData;

    Connections
    {
        target: server;

        onDilersDataUpdated:
        {
            console.log(" ========= onDilersDataUpdated =========");
            for(var i = 0; i < dilersData[0].dilersInCity.length; i++)
            {
                cityModel.append({"text": dilersData[i].name});
            }
            dilData = dilersData;
            calculateDilers(0);
        }
    }

    function calculateDilers(id)
    {
        dilersModel.clear();
        for(var j = 0; j < dilData[id].dilersInCity.length; j++)
        {
            dilersModel.append({"text": dilData[id].dilersInCity[j].name});
        }
        dilersCombo.currentIndex = 0;
    }

    function start()
    {
        visible = true;
        testDrive.animComplete();
         server.getDealersRequest();
    }

    function stop()
    {
        visible = false;
    }
}
