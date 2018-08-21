#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

class SerialThread : public QObject
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();

    void initThread(QThread* thread);
    void setPortName(const QString& value);


private:
    QTimer* reconnectTimer = nullptr;
    QTimer* noDataTimer = nullptr;
    QSerialPort* serialPort = nullptr;

    QString portName;


    void tryReconnect();

private slots:
    virtual void onReadyRead();
    void onReadError(QSerialPort::SerialPortError serialPortError);
    void startReading();

    void onReconnectHandle();
    void onNoDataTimerHandle();

signals:
     void dataRecieve(const QByteArray&);
};


#endif // SERIALTHREAD_H
