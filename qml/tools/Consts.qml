import QtQuick 2.0

Item
{
    property real animFPS: 24.0;
    property real designScale: 1.0;//standData.mainConfig.touchScreen.width / 1080.0;

    property string infoTextColor: "#009999";

    property string cityMapUrl : "qrc:/resources/gameplay-new.jpg";
    property int canvasY: 0;
    property int lineWidth: 10;
    property string lineCap: "round";
    property string lineJoin: "round";

    property double scaleFactor: 1;//1.25;//9375;
    property double artScaleFactor: 1;//0.925;

    property string carUrl: "qrc:/resources/car2.png";
    property string carShadowUrl: "qrc:/resources/shadow.png";
    property int carWidth: 64;//30;
    property int carHeight: 124;//54;
    property int carAddAngle: -90 + 180;

    property int bulletSize: 10;
    property int finishBulletSize: finBulletSizeAnimateHelper.size;

    property var redColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var finishBulletColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var startBulletColor:  Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var guideColor: Qt.rgba(0.9, 0.0, 0.0, animateHelper.opacity);

    property double toDegrees: 180 / Math.PI;

    Component.onCompleted:
    {

    }

    Item {
        id: animateHelper
        opacity: 0
        PropertyAnimation { id: opacityAnimtor;
            target: animateHelper;
            property: "opacity";
            from: 0;
            to: 0.5;
            duration: 500 }
    }

    Item {
        id: finBulletSizeAnimateHelper
        property int size: 40;
        PropertyAnimation { id: sizeAnimtor;
            target: finBulletSizeAnimateHelper;
            property: "size";
            from: 10;
            to: 20;
            duration: 500
        }
    }

    function animateGuideColor()
    {
        sizeAnimtor.start();
        opacityAnimtor.start();
    }
}
