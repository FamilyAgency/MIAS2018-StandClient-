#include "UserData.h"

UserData::UserData(QObject *parent) : QObject(parent)
{

}

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
}

QVariantList UserData::prizes() const
{
    return _prizes;
}

void UserData::setPrizes(const QVariantList& value)
{
    _prizes = value;
    emit prizesChanged();
}

QString UserData::name() const
{
    return _name;
}

QString UserData::surname() const
{
    return _surname;
}

int UserData::id() const
{
    return _id;
}

bool UserData::exist() const
{
    return _exist;
}

bool UserData::firstTime() const
{
    return _firstTime;
}

bool UserData::finished() const
{
    return _finished;
}

bool UserData::waitEnoughToPlay() const
{
    return _waitEnoughToPlay;
}

void UserData::setName(const QString& value)
{
    _name = value;
    emit nameChanged();
}

void UserData::setSurname(const QString& value)
{
    _surname = value;
    emit surnameChanged();
}

void UserData::setId(int value)
{
    _id = value;
    emit idChanged();
}

void UserData::setExist(bool value)
{
    _exist = value;
    emit existChanged();
}

void UserData::setFirstTime(bool value)
{
    _firstTime = value;
    emit firstTimeChanged();
}

void UserData::setFinished(bool value)
{
    _finished = value;
     emit finishedChanged();
}

void UserData::setWaitEnoughToPlay(bool value)
{
    _waitEnoughToPlay = value;
    emit waitEnoughToPlayChanged();
}

void UserData::setGameProgess(GameProgress* value)
{
    gameProgress = value;
}

GameProgress* UserData::getGameProgess()
{
    return gameProgress;
}

void UserData::clearData()
{

}

