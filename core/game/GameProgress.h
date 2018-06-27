#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>

class GameProgress : public QObject
{
    Q_OBJECT
public:
    explicit GameProgress(QObject *parent = nullptr);

private:


signals:

public slots:
};

#endif // GAMEPROGRESS_H
