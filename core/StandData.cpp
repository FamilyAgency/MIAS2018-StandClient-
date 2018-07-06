#include "StandData.h"
#include <QGuiApplication.h>
#include <QScreen.h>

StandData::StandData(QObject *parent) : QObject(parent)
{

}

void StandData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("standData", this);
}

void StandData::setConfig(ConfigPtr value)
{
   setMainConfig(*value->mainConfig);
}

void StandData::setMainConfig(MainConfig config)
{
    _mainConfig = config;
    emit mainConfigChanged();
}

MainConfig StandData::mainConfig() const
{
    return _mainConfig;
}

QVariantList StandData::getScreensInfo() const
{
    QVariantList infoList;
    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    auto screens = QGuiApplication::screens();

    QString info;
    for(QScreen* screen : screens)
    {
        auto geometry = screen->geometry();
        QString x0 = QString::number(geometry.x());
        QString y0  =  QString::number(geometry.y());
        QString width = QString::number(geometry.width());
        QString height =  QString::number(geometry.height());
        QString sizes = "(" + x0 + ", " + y0 + ", "  + width + ", " + height+ ")";
        info = screen->name() + " " + sizes;

        if(primaryScreen->name() == screen->name())
        {
            info += " primary";
        }

        infoList.append(info);
    }

    return infoList;
}
