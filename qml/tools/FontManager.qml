import QtQuick 2.0

Item
{
    property alias hyundaiSansHeadMedium: hyundaiSansHeadMedium.name;
    property alias hyundaiSansHeadRegular: hyundaiSansHeadRegular.name;
    property alias hyundaiSansHeadBold: hyundaiSansHeadBold.name;
	property alias hyundaiSansHeadLight: hyundaiSansHeadLight.name;
    property alias rfg79: rfg79.name;

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

	FontLoader
	{
		id: hyundaiSansHeadLight;
		source: configController.getFileInAppDir("content/fonts/HyundaiSansHeadOffice-Light.ttf");
	}

    FontLoader
    {
        id: rfg79;
        source: configController.getFileInAppDir("content/fonts/RFG79.otf");
    }


}
