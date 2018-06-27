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

    QString name() const;
    QString surname() const;
    int id() const;
    bool isExists() const;
    bool isFirstTime() const;
    bool isFinished() const;
    bool isGetPrize() const;
    bool isWaitEnoughToPlay() const;

    void setName(const QString& value);
    void setSurname(const QString& value);
    void setId(int value);
    void setExists(bool value);
    void setFirstTime(bool value);
    void setFinished(bool value);
    void setGetPrize(bool value);
    void setWaitEnoughToPlay(bool value);

    void setQmlContext(QQmlContext* value);
    void setGameProgess(GameProgress* value);
    void clearData();

    GameProgress* getGameProgess();

private:
    QString _name;
    QString _surname;
    int _id = -1;

    bool _isExists;
    bool _isFirstTime;
    bool _isFinished;
    bool _isGetPrize;
    bool _isWaitEnoughToPlay;

    QQmlContext* qmlContext;
    GameProgress* gameProgress;

signals:
    void nameChanged();
    void surnameChanged();
    void idChanged();
public slots:
};

#endif // USERDATA_H
