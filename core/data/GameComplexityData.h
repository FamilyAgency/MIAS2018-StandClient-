#ifndef GAMECOMPLEXITYDATA_H
#define GAMECOMPLEXITYDATA_H

#include <QObject>
#include "config/Config.h"

class GameComplexityData : public QObject
{
    Q_OBJECT
public:
    explicit GameComplexityData(QObject *parent = nullptr);
    virtual ~GameComplexityData();

    void setConfig(ConfigPtr value);

    QVector<OneGameComplexityConfig> gameComplexities;
    OneGameComplexityConfig superGameComplexity;
    int instruction;
    int roulette;

    void start();
    void setServerComponent(QSharedPointer<class ServerComponent> value);
    void checkComplexity();

private:
    ComplexityConfig complexityConfig;
    QSharedPointer<class ServerComponent> serverComponent = nullptr;

private slots:
    void onNewGameComplexity(const ComplexityConfig& value);

};

#endif // GAMECOMPLEXITYDATA_H
