#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <QQmlContext>

class UserData : public QObject
{
    Q_OBJECT
public:
    explicit UserData(QObject *parent = nullptr);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    //GameData

     QString name() const;
     QString surname() const;
     int id() const;

     void setName(const QString& value);
     void setSurname(const QString& value);
     void setId(int value);

     void setQmlContext(QQmlContext* value);

private:
     QString _name;
     QString _surname;
     int _id = -1;
     QQmlContext* qmlContext;

signals:
     void nameChanged();
     void surnameChanged();
     void idChanged();
public slots:
};

#endif // USERDATA_H
