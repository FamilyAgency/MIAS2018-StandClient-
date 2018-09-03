import QtQuick 2.0

Item
{
    property real animFPS: 24.0;
    property real designScale: 1.0;//standData.mainConfig.touchScreen.width / 1080.0;

    property string infoTextColor: "#009999";
    property int canvasY: 0;
    property int lineWidth: 10;
    property string lineCap: "round";
    property string lineJoin: "round";

    property double scaleFactor: 1;//1.25;//9375;
    property double artScaleFactor: 1;//0.925;

    property string carUrl: "qrc:/resources/car2.png";
    property string carShadowUrl: "qrc:/resources/Glow_Car.png";
    property int carWidth: 64;
    property int carHeight: 124;
    property int carAddAngle: -90 + 180;

    property int bulletSize: 10;

    property var redColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var finishBulletColor: Qt.rgba(0., 164./255., 227.0 / 255., 1);
    property var startBulletColor:  Qt.rgba(0., 164./255., 227.0 / 255., 1);

    property double toDegrees: 180 / Math.PI;
}
