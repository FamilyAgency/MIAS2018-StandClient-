#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>
#include <QQmlContext>
#include "config/Config.h"

class StandData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainConfig mainConfig READ mainConfig WRITE setMainConfig NOTIFY mainConfigChanged)
    Q_PROPERTY(QString buildNumber READ buildNumber WRITE setBuildNumber NOTIFY buildNumberChanged)

public:
    Q_INVOKABLE QVariantList getScreensInfo() const;
    Q_INVOKABLE QString getStandImage(const QString& path) const;
    Q_INVOKABLE QString getStandMap() const;
    Q_INVOKABLE QString getStandMapOver() const;

    explicit StandData(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    void setConfig(ConfigPtr config);

    void setMainConfig(MainConfig config);
    MainConfig mainConfig() const;

    void setBuildNumber(const QString& value);
    QString buildNumber() const;

private:   
    QQmlContext* qmlContext;
    MainConfig _mainConfig;
    QString _buildNumber = "1.4v";

    QString getStandPath() const;

signals:
    void mainConfigChanged();
    void buildNumberChanged();

};

#endif // STANDINFO_H
