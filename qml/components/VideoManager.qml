import QtQuick 2.0

Item
{
    property string intro1Path: configController.getVideoFileInAppDir("content/video/intro1");
    property string intro2Path: configController.getVideoFileInAppDir("content/video/intro2");
    property string instructionPath: configController.getVideoFileInAppDir("content/video/instruction");
    property string bgLoop: configController.getVideoFileInAppDir("content/video/bgloop");

}
