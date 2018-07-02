#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <QQmlContext>
#include "core/game/GameProgress.h"

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool exist READ exist WRITE setExist NOTIFY existChanged)
    Q_PROPERTY(bool firstTime READ firstTime WRITE setFirstTime NOTIFY firstTimeChanged)
    Q_PROPERTY(bool finished READ finished WRITE setFinished NOTIFY finishedChanged)
    Q_PROPERTY(bool waitEnoughToPlay READ waitEnoughToPlay WRITE setWaitEnoughToPlay NOTIFY waitEnoughToPlayChanged)
    Q_PROPERTY(QVariantList prizes READ prizes WRITE setPrizes NOTIFY prizesChanged)

    const int maxPrizesCount = 2;

    QString name() const;
    QString surname() const;
    int id() const;
    bool exist() const;
    bool firstTime() const;
    bool finished() const;
    QVariantList prizes() const;
    bool waitEnoughToPlay() const;

    void setName(const QString& value);
    void setSurname(const QString& value);
    void setId(int value);
    void setExist(bool value);
    void setFirstTime(bool value);
    void setFinished(bool value);
    void setPrizes(const QVariantList& value);
    void setWaitEnoughToPlay(bool value);

    void setQmlContext(QQmlContext* value);
    void setGameProgess(GameProgress* value);
    void clearData();

    GameProgress* getGameProgess();
    OneGameData getCurrentGameData() const;
    void currentGameCompleted(int time);
    bool hasGames() const;

private:
    QString _name = "Unknown";
    QString _surname = "Unknown";
    int _id = -1;

    bool _exist = false;
    bool _firstTime = false;
    bool _finished = false;
    QVariantList _prizes;
    bool _waitEnoughToPlay = false;

    QQmlContext* qmlContext;
    GameProgress* gameProgress;

signals:
    void nameChanged();
    void surnameChanged();
    void idChanged();
    void existChanged();
    void firstTimeChanged();
    void waitEnoughToPlayChanged();
    void finishedChanged();
    void prizesChanged();
};

#endif // USERDATA_H
