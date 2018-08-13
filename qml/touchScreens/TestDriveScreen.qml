import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import "elements"
import "supergame"
import "../tools"

Item
{
    id: testDrive;

    anchors.fill: parent;
    anchors.centerIn: parent;

    property string mainTitleDefault: "ТЕСТ ДРАЙВ";
    property string buttonText: "ЗАПИСАТЬСЯ";
    property string okText: "Спасибо!<br/>Ваш запрос отправлен.";

    property var allDealersData;
    property real btnMarginBottom: 100 * consts.designScale;

    signal animComplete();
    signal animStart();

    Consts
    {
        id: consts;
    }

    FontManager
    {
        id: font;
    }

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
        id:columns;
        spacing: 100;
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
                id: dealersModel
            }
        }
    }

    Text
    {
        id: okFiled;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.verticalCenter: parent.verticalCenter;
        text: okText;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize: 80 * consts.designScale;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment :Text.AlignHCenter;

        OpacityAnimator on opacity
        {
            id: opacityAnim;
            from: 0;
            to: 1;
            duration: 700;
            running: false;
            easing.type: "InOutCubic";

            onStopped:
            {
                if( okFiled.opacity == 0)
                {
                    appController.backToIntro();
                }
            }
        }

        ScaleAnimator on scale
        {
            id: scaleAnim;
            from: 0.5;
            to: 1;
            duration: 700;
            running:false;
            easing.type: "OutCubic";
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

    Timer
    {
        id:outTimer;
        running: false;
        interval: 2000;
        onTriggered:
        {

            opacityAnim.from = 1;
            opacityAnim.to = 0;
            opacityAnim.start();

            scaleAnim.from = 1;
            scaleAnim.to = 0;
            scaleAnim.start();
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

            opacityAnim.from = 0;
            opacityAnim.to = 1;
            opacityAnim.start();

            scaleAnim.from = 0.5;
            scaleAnim.to = 1;
            scaleAnim.start();

            outTimer.start();
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
        columns.visible = true;
        citiesComboBox.currentIndex = 0;
        dealersComboBox.currentIndex = 0;
        visible = true;
        testDrive.animComplete();

        startBtn.show();

        okFiled.scale = 0;
        okFiled.opacity = 0;
    }

    function stop()
    {
        visible = false;
    }
}
