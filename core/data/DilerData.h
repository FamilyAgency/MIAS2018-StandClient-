#ifndef DILERDATA_H
#define DILERDATA_H

#include <QObject>
#include <QVariantList>

struct OneDilerData
{
private:
    Q_GADGET
    Q_PROPERTY(int dealer_id MEMBER dealer_id)
    Q_PROPERTY(QString name MEMBER name)
public:
    int dealer_id = 0;
    QString name = "";

};
Q_DECLARE_METATYPE(OneDilerData)


struct DilerCityData
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QVariantList dilersInCity MEMBER dilersInCity)
public:
    int id = 0;
    QString name = "";
    QVariantList dilersInCity;

};
Q_DECLARE_METATYPE(DilerCityData)


class DilerData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList cities READ cities WRITE setCities NOTIFY citiesChanged)

public:
    explicit DilerData(QObject *parent = nullptr);

    void setCities(const QVariantList& value)
    {
        _cities = value;
        emit citiesChanged();
    }

    QVariantList cities() const
    {
        return _cities;
    }

private:
    QVariantList _cities;

signals:
    void citiesChanged();

public slots:
};

#endif // DILERDATA_H
