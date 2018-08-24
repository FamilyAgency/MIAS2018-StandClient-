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

    void setNoDataTimeoutMills(int value);
    void setReconnectionMills(int value);

private:

    int noDataTimeoutMills = 5000;
    int reconnectionMills = 1000;

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
     void connectionError();
     void noDataTimeout();
     void connectionSuccess();
};


#endif // SERIALTHREAD_H
