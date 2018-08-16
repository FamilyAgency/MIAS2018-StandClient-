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

	ListModel
	{
		id: citiesModel;

		ListElement { name: "Абаза" }
		ListElement { name: "Балашиха" }
		ListElement { name: "Верея" }
		ListElement { name: "Верхоянск" }
		ListElement { name: "Москва" }
		ListElement { name: "Москва и подмосковье" }
		ListElement { name: "Новосибирск" }
		ListElement { name: "Самара" }
	}

	ListModel
	{
		id: dealerModel;
		ListElement { name: "Абаза" }
		ListElement { name: "Абаза" }
		ListElement { name: "Абаза" }
		ListElement { name: "Абаза" }
		ListElement { name: "Абаза" }
	}

//	ListModel
//	{
//		id: testModel;
////		model: ["Adan Gula","Alexandria Armand","Alverta Gorney","Annalisa Dixion","Arlene Drapeau","Ashely Euler","Ashleigh Terry","Audra Vannorman","Bibi Fraire", "Branda Melgoza","Breanna Rotenberry","Brigette Delk","Bruno Raso","Calandra Dudney","Carrol Dedeaux","Celina Bichrest","Celinda Frutos","Celsa Moen","Charise Milan","Corazon Burrus","Coreen Dehner","Coretta Stillwell","Cornell Fierros","Deedee Ruggerio","Demetrice Mcclaren","Desiree Marcano","Dimple Harig","Divina Fahie","Don Thill","Ellena Fredrick","Elmo Routh","Elsie Raulerson","Ervin Bardsley","Estela Alverson","Eufemia Sheely","Fawn Opie","Fred Ralphs","Genevie Spires","Genna Quin","Gerri Aden","Gianna Shears","Gilda Doyel","Glady Peguero","Guy Sondag","Herschel Flowers","Hilda Hamm","Hiroko Mccarley","Jackeline Millington","Jacqualine Twiss","Jacquelyne Worsley","Janelle Broman","Jani Reddish","Jasper Krone","Jene Gump","Jimmie Cooley","Kellye Wiest","Kristie Jules","Kymberly Moodie","Latesha Netter","Lavelle Lasala","Lesli Czapla","Lorette Prescott","Lorie Hoeft","Lyndia Schwalm","Mable Marron","Marcelino Spence","Marcie Yopp","Margrett Spagnuolo","Maris Ruff","Marvella Bowlby","Mauro Winberg","Maybelle Chute","Meghan Burts","Micah Hoggan","Mireille Eastin","Mitsue Ohler","Monica Mccall","Morris Cappel","Myong Bale","Nannie Poore","Noella Gledhill","Ofelia Bane","Phoebe Bui","Quincy Sweeting","Raguel Ross","Raymundo Headlee","Ressie Helt","Rikki Gilligan","Roselee Swain","Shanda Ballew","Stephine Dimauro","Tamesha Roop","Temple Mcbain","Tiesha Crumley","Tova Kiel","Wade Fossum","Willodean Ferguson","Winfred High","Winter Furrow","Yvone Edge"]
//	}

	SwipeView
	{
		id: swiper;

		currentIndex: 0;
		anchors.fill: parent;

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
						swiper.currentIndex = 1;
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
						swiper.currentIndex = 0;
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
					// var dealerName = allDealersData[chooseCityIndex].dealers[index].name;
					//console.log(index, dealerName);
					calculateDealersByCityId(index);
					dealerBtn.choosenIndex = index;
					swiper.currentIndex = 0;
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


	FontManager
	{
		id: font;
	}

	Consts
	{
		id: consts;
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
			visible: false;
			id: citiesComboBox;
			currentIndex: 0;
			implicitWidth: 500;

//            model:ListModel
//            {
//                id: cityModel;
//            }

			onCurrentIndexChanged:
			{
				calculateDealersByCityId(currentIndex);
			}
		}

		ComboBox
		{
			id: dealersComboBox;
			visible: false;
			currentIndex: 0;
			implicitWidth: 500;
//            model:ListModel
//            {
//                id: dealersModel;
//            }
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
		cleanUp();

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

	function cleanUp()
	{
		citiesListView.positionViewAtBeginning();
		dealersListView.positionViewAtBeginning();
		citiesBtn.choosenIndex = -1;
		dealerBtn.choosenIndex = -1;


	}
}
