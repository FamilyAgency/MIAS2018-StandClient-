#ifndef GAMECOMPLEXITYDATA_H
#define GAMECOMPLEXITYDATA_H

#include <QObject>
#include "config/Config.h"
//#include "components/ServerComponent.h"

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

    void update();
    void start();
    //void setServerComponent(QSharedPointer<ServerComponent> value);

private:
    ComplexityConfig complexityConfig;
  //  QSharedPointer<ServerComponent> serverComponent = nullptr;

private slots:
    void onNewGameComplexity(const ComplexityConfig& value);

};

#endif // GAMECOMPLEXITYDATA_H
