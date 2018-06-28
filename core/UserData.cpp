#include "UserData.h"

UserData::UserData(QObject *parent) : QObject(parent)
{

}

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
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

bool UserData::isExists() const
{
    return _isExists;
}

bool UserData::isFirstTime() const
{
    return _isFirstTime;
}

bool UserData::isFinished() const
{
    return _isFinished;
}

bool UserData::isWaitEnoughToPlay() const
{
    return _isWaitEnoughToPlay;
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

void UserData::setExists(bool value)
{
    _isExists = value;
}

void UserData::setFirstTime(bool value)
{
    _isFirstTime = value;
}

void UserData::setFinished(bool value)
{
    _isFinished = value;
}

void UserData::setSuperPrizeRecieved(bool value)
{
    _isSuperPrizeRecieved = value;
}

void UserData::setColaPrizeRecieved(bool value)
{
    _isColaPrizeRecieved = value;
}

bool UserData::isSuperPrizeRecieved() const
{
    return _isSuperPrizeRecieved;
}

bool UserData::isColaPrizeRecieved() const
{
    return _isColaPrizeRecieved;
}

void UserData::setWaitEnoughToPlay(bool value)
{
    _isWaitEnoughToPlay = value;
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








