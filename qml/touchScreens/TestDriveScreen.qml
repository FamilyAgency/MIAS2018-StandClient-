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
    property var allDealersData;

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

        ComboBox
        {
            id: citiesComboBox;
            currentIndex: 0;
            implicitWidth: 500;

            model:ListModel
            {
                id: cityModel;
            }            

            onCurrentIndexChanged:
            {
                calculateDealersByCityId(currentIndex);
            }
        }

        ComboBox
        {
            id: dealersComboBox;
            currentIndex: 0;
            implicitWidth: 500;
            model:ListModel
            {
                id: dealersModel
            }

        }

        Button
        {
            text:"Test Drive";

            onClicked:
            {

                var cityIndex = citiesComboBox.currentIndex;
                var dealerIndex = dealersComboBox.currentIndex;
                var dealerId = allDealersData[cityIndex].dealers[dealerIndex].id;
                console.log("send test drive ", dealerId)
                testDriveModule.makeTestDrive(dealerId);
            }

            background: Rectangle
            {
                implicitWidth: 200;
                color: "#ffffff";
            }
        }
    }


    Connections
    {
        target: testDriveModule;

        onDealersDataUpdated:
        {
            console.log(" ========= onDilersDataUpdated =========");
            citiesComboBox.currentIndex = 0;
            dealersComboBox.currentIndex = 0;
            allDealersData = allDealers;

            for(var i = 0; i < allDealers.length; i++)
            {
                cityModel.append({"text": allDealers[i].name});
            }

            calculateDealersByCityId(0);
        }
    }

    function calculateDealersByCityId(id)
    {
        dealersModel.clear();
        var city = allDealersData[id];

        for(var j = 0; j < city.dealers.length; j++)
        {
            dealersModel.append({"text": city.dealers[j].name});
        }

        dealersComboBox.currentIndex = 0;
    }

    function start()
    {
        citiesComboBox.currentIndex = 0;
        dealersComboBox.currentIndex = 0;
        visible = true;
        testDrive.animComplete();
    }

    function stop()
    {
        visible = false;
    }
}
