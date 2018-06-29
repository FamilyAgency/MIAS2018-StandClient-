#ifndef TASKCREATOR_H
#define TASKCREATOR_H

#include <QObject>
#include "core/game/GameTask.h"
#include "core/UserData.h"

class TaskCreator : public QObject
{
    Q_OBJECT
public:
    explicit TaskCreator(QObject *parent = nullptr);
     QMap<int, QSharedPointer<GameTask>> create(UserData* value);
};

#endif // TASKCREATOR_H
