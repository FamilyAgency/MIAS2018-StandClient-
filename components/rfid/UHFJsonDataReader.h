#ifndef UHFJSONDATAREADER_H
#define UHFJSONDATAREADER_H

#include <QObject>
#include "components/rfid/UHFDataReader.h"

class UHFJsonDataReader : public UHFDataReader
{
    Q_OBJECT
public:
    explicit UHFJsonDataReader(QObject *parent = nullptr);

signals:

public slots:
    virtual void onReadyRead() override;
    void create_hex_str(std::vector<uint8_t> data, std::string &tgt);
};

#endif // UHFJSONDATAREADER_H
