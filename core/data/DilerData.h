#ifndef DILERDATA_H
#define DILERDATA_H

#include <QObject>
#include <QVariantList>

struct OneDealerData
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
public:
    int id = 0;
    QString name = "";
};
Q_DECLARE_METATYPE(OneDealerData)

struct DealerCityData
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QVariantList dealers MEMBER dealers)
public:
    int id = 0;
    QString name = "";
    QVariantList dealers;
};
Q_DECLARE_METATYPE(DealerCityData)


class DilerData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList dealers READ dealers WRITE setDealers NOTIFY dealersChanged)

public:
    explicit DilerData(QObject *parent = nullptr);

    void setDealers(const QVariantList& value);
    QVariantList dealers() const;

private:
    QVariantList _dealers;

signals:
    void dealersChanged();

};

#endif // DILERDATA_H
