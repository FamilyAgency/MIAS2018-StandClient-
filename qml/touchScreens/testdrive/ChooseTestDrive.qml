import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../elements"
import "../../tools"

Item
{
    property var allDealersData;
    property real btnMarginBottom: 100 * consts.designScale;

    property string buttonText: "ЗАПИСАТЬСЯ";

    anchors.fill: parent;
    anchors.centerIn: parent;


    ListModel
    {
        id: cityModel1;

        ListElement
        {
            name: "A"
            type: "serviceItem"
        }

        ListElement
        {
            name: "Алма-Аты"
            type: "playableItem"
        }

        ListElement
        {
            name: "Б"
            type: "serviceItem"
        }
    }

    ListModel
    {
        id: dealerModel1;

        ListElement
        {
            name: "A"
            type: "serviceItem"
        }

        ListElement
        {
            name: "Алма-Аты"
            type: "playableItem"
        }

        ListElement
        {
            name: "Б"
            type: "serviceItem"
        }
    }


    ColumnLayout
     {
         //1.1 maindealerButton - city
         // setmodelitem
         // show, hide


         // 1.2 maindealerButton - dealer in city



         //testDriveListview - container for model
         // settitle
         // setmodel
         // show/hide
         // signal onitemchoosen
         // on closed

     }

    ColumnLayout
    {
        id:columns;
        spacing: 100;
        visible: false;
        y:400;
        anchors.horizontalCenter: parent.horizontalCenter;

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
                id: dealersModel;
            }
        }
    }

    BigRedButton
    {
        id: startBtn;

        anchors.bottomMargin: btnMarginBottom;
        visible: false;
        anchors.fill: parent;
        btnWidth: 350 * consts.designScale;
        btnHeight: 350 * consts.designScale;
        btnRadius: 175 * consts.designScale;

        onClicked:
        {
            var cityIndex = citiesComboBox.currentIndex;
            var dealerIndex = dealersComboBox.currentIndex;
            var dealerId = allDealersData[cityIndex].dealers[dealerIndex].id;
            console.log("send test drive ", dealerId)
            testDriveModule.makeTestDrive(dealerId);
        }
    }

    Component.onCompleted:
    {
        startBtn.setTitle(buttonText);
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

        onTestDriveRequestSuccess:
        {
            columns.visible = false;
            startBtn.hide();
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
        visible = true;

        columns.visible = true;
        citiesComboBox.currentIndex = 0;
        dealersComboBox.currentIndex = 0;

        startBtn.show();
    }

    function stop()
    {
        visible = false;
    }
}
