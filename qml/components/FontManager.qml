import QtQuick 2.0

Item
{
    property alias hyundaiSansHeadMedium: hyundaiSansHeadMedium.name;
    property alias hyundaiSansHeadRegular: hyundaiSansHeadRegular.name;

    FontLoader
    {
        id: hyundaiSansHeadMedium;
        source: configController.getFileInAppDir("content/fonts/HyundaiSansHeadOffice-Medium.ttf");
    }

    FontLoader
    {
        id: hyundaiSansHeadBold;
        source: configController.getFileInAppDir("content/fonts/HyundaiSansHeadOffice-Bold.ttf");
    }

    FontLoader
    {
        id: hyundaiSansHeadRegular;
        source: configController.getFileInAppDir("content/fonts/HyundaiSansHeadOffice-Regular.ttf");
    }
}
