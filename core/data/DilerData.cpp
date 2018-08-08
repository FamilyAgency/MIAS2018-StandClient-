#include "DilerData.h"

DilerData::DilerData(QObject *parent) : QObject(parent)
{

}

void DilerData::setDealers(const QVariantList& value)
{
    _dealers = value;
    emit dealersChanged();
}

QVariantList DilerData::dealers() const
{
    return _dealers;
}
