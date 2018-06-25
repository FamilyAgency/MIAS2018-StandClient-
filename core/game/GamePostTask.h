#ifndef GAMEPOSTTASK_H
#define GAMEPOSTTASK_H

#include <QObject>

class GamePostTask : public QObject
{
    Q_OBJECT
public:
    explicit GamePostTask(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GAMEPOSTTASK_H