import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import "../elements"
import "../../tools"

Item
{
    property var allDealersData;
    property real btnMarginBottom: 100 * consts.designScale;


    property string signInText: "Запись\nна тест-драйв";
    property string signInDescText: "Познакомься с увлекательным\nмиром Sata Fe!";
    property string citiesBtnText: "Выберите ваш город";
    property string dealerBtnText: "Выберите вашего дилера";
    property string buttonText: "ЗАПИСАТЬСЯ";

    anchors.fill: parent;
    anchors.centerIn: parent;

    SwipeView
    {
        id: swiper;
        currentIndex: 0;
        anchors.fill: parent;
        interactive: false;

        Item
        {
            Column
            {
                id: mainItem;

                anchors.fill: parent;
                anchors.topMargin: 100;
                anchors.bottomMargin: 100;
                anchors.leftMargin: 150;
                anchors.rightMargin: 150;
                spacing: 50;

                Text
                {
                    text: signInText;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: font.hyundaiSansHeadBold;
                    font.pixelSize: 80;
                    font.bold: true;
                    wrapMode: Text.Wrap;
                    color: "white";
                }

                Text
                {
                    text: signInDescText;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                    horizontalAlignment: Text.AlignHCenter;
                    font.family: font.hyundaiSansHeadRegular;
                    font.pixelSize: 50;
                    wrapMode: Text.Wrap;
                    color: "white";
                }

                Item//spacer
                {
                    height: 150;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                }

                ChooseButton
                {
                    id: citiesBtn;
                    btnColor: "#112041";
                    btnText: citiesBtnText;

                    onClicked:
                    {
                        citiesListView.positionViewAtBeginning();
                        swiper.currentIndex = 1;
                        startBtn.hide();
                    }

                    onChoosenIndexChanged:
                    {
                        if (choosenIndex === -1)
                        {
                            btnText = citiesBtnText;
                        }
                        else
                        {
                            btnText = allDealersData[choosenIndex].name;
                        }
                    }
                }

                Item//spacer
                {
                    height: 2;
                    anchors.left: parent.left;
                    anchors.right: parent.right;
                }

                ChooseButton
                {
                    id: dealerBtn;
                    btnColor: "#112041";
                    btnText: dealerBtnText;

                    onClicked:
                    {
                        if (citiesBtn.choosenIndex !== -1)
                        {
                            dealersListView.positionViewAtBeginning();
                            calculateDealersByCityId(citiesBtn.choosenIndex);
                            swiper.currentIndex = 2;
                            startBtn.hide();
                        }
                    }

                    onChoosenIndexChanged:
                    {
                        if (choosenIndex === -1)
                        {
                            btnText = dealerBtnText;
                        }
                        else
                        {
                            btnText = allDealersData[citiesBtn.choosenIndex].dealers[dealerBtn.choosenIndex].name;
                        }
                    }
                }
            }
        }

        // _____________END MAIN ITEM____________________

        Item
        {
            TestDriveListView
            {
                id: citiesListView;

                model: ListModel
                {
                    id: cityModel;
                }

                onItemChoosen:
                {

                    //var cityIndex = citiesComboBox.currentIndex;
                    //var dealerIndex = dealersComboBox.currentIndex;
                    //var dealerId = allDealersData[cityIndex].dealers[dealerIndex].id;
                    console.log(index, allDealersData[index].name);
                    calculateDealersByCityId(index);
                    citiesBtn.choosenIndex = index;
                    swiper.currentIndex = 2;
                }
            }

            Rectangle
            {
                width: 5;
                anchors.right: parent.right;
                anchors.top: parent.top;
                height: citiesListView.height * citiesListView.visibleArea.yPosition * 1 + 100;
                color: "#0893b7";
            }

            CloseButton
            {
                onClicked:
                {
                    swiper.currentIndex = 0;
                }
            }
        }

        Item
        {
            TestDriveListView
            {
                id: dealersListView;
                model:ListModel
                {
                    id: dealersModel;
                }

                onItemChoosen:
                {
                    calculateDealersByCityId(index);
                    dealerBtn.choosenIndex = index;
                    swiper.currentIndex = 0;
                    startBtn.show();
                }
            }

            Rectangle
            {
                width: 5;
                anchors.right: parent.right;
                anchors.top: parent.top;
                height: citiesListView.height * citiesListView.visibleArea.yPosition * 1 + 100;
                color: "#0893b7";
            }

            CloseButton
            {
                onClicked:
                {
                    swiper.currentIndex = 0;
                }
            }
        }
    }// ________________END SWIPER________________________


    FontManager
    {
        id: font;
    }

    Consts
    {
        id: consts;
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
            var cityIndex = citiesBtn.choosenIndex;
            var dealerIndex = dealerBtn.choosenIndex;
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
            allDealersData = allDealers;

            for(var i = 0; i < allDealers.length; i++)
            {
                cityModel.append({"text": allDealers[i].name});
            }

            calculateDealersByCityId(0);
        }

        onTestDriveRequestSuccess:
        {
            visible = false;
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
    }

    function start()
    {
        cleanUp();
        visible = true;
    }

    function stop()
    {
        visible = false;
    }

    function cleanUp()
    {
        citiesListView.positionViewAtBeginning();
        dealersListView.positionViewAtBeginning();
        citiesBtn.choosenIndex = -1;
        dealerBtn.choosenIndex = -1;
        swiper.currentIndex = 0;
    }
}
