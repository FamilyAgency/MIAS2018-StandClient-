#ifndef ADVANTAGESDATA_H
#define ADVANTAGESDATA_H

#include <QObject>
#include "config/Config.h"

class AdvantagesData : public QObject
{
    Q_OBJECT
public:
    explicit AdvantagesData(QObject *parent = nullptr);

    void setConfig(ConfigPtr value);
    OneAdvantageConfig getNextAdvantage();
    void shuffle();

private:
    AdvantagesConfig advantagesConfig;
    QVector<OneAdvantageConfig> advantages;
    int advantageIndex = 0;

};

#endif // ADVANTAGESDATA_H
