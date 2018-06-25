#ifndef STANDINFO_H
#define STANDINFO_H

#include <QObject>
#include <QQmlContext>

class StandData : public QObject
{
    Q_OBJECT
public:
    explicit StandData(QObject *parent = nullptr);
    void setQmlContext(QQmlContext* value);

    Q_INVOKABLE int getStandId() const;

private:
    int standId = 11;
    QQmlContext* qmlContext;

signals:

public slots:

};

#endif // STANDINFO_H
