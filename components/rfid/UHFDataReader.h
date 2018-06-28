#ifndef UHFDATAREADER_H
#define UHFDATAREADER_H

#include <QObject>
#include "components/rfid/BaseRFIDDataReader.h"

class UHFDataReader : public BaseRFIDDataReader
{
    Q_OBJECT
public:
    explicit UHFDataReader(QObject *parent = nullptr);

    virtual void startReading(int modelIndex) override;

private:
    const int taskTimerMills = 100;
    QTimer* timer;

    QByteArray beepOnCommand;
    QByteArray beepOffCommand;
    QByteArray readCommand;
    QByteArray inventoryCommand;
    QByteArray clearCommand;
    QByteArray resetCommand;

signals:

private slots:
    void onUpdate();
     virtual void onReadyRead() override;
};

#endif // UHFDATAREADER_H
