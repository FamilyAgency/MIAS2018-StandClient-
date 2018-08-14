#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class StandData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainConfig mainConfig READ mainConfig WRITE setMainConfig NOTIFY mainConfigChanged)

public:
    Q_INVOKABLE QVariantList getScreensInfo() const;
    Q_INVOKABLE QString getStandImage(const QString& path) const;
    Q_INVOKABLE QString getStandMap() const;

    explicit StandData(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    void setConfig(ConfigPtr config);

    void setMainConfig(MainConfig config);
    MainConfig mainConfig() const;

private:   
    QQmlContext* qmlContext;
    MainConfig _mainConfig;   

signals:
    void mainConfigChanged();

};

#endif // STANDINFO_H
