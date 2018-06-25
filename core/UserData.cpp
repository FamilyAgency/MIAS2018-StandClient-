#include "UserData.h"

UserData::UserData(QObject *parent) : QObject(parent)
{

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

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
}


