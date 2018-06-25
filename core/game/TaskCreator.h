#ifndef TASKCREATOR_H
#define TASKCREATOR_H

#include <QObject>
#include "core/game/GameTask.h"

class TaskCreator : public QObject
{
    Q_OBJECT
public:
    explicit TaskCreator(QObject *parent = nullptr);

    virtual QList<GameTask*> create();

signals:

public slots:
};

#endif // TASKCREATOR_H
