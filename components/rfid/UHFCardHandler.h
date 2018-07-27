#ifndef UHFDATAREADER_H
#define UHFDATAREADER_H

#include <QObject>
#include "components/RFIDComponent.h"

class UHFCardHandler : public RFIDComponent
{
    Q_OBJECT
public:
    explicit UHFCardHandler(QObject *parent = nullptr);

    virtual void startReading() override;

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
    virtual void onReadyRead();
};

#endif // UHFDATAREADER_H
