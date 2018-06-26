#include "ArduinoComponent.h"

ArduinoComponent::ArduinoComponent(QObject *parent) : ExternalSystemComponent(parent)
{
    name = "Arduino";
}

void ArduinoComponent::setConfig(const ArduinoConfig& config)
{
    arduinoConfig = config;
    emit configChanged();
}

void ArduinoComponent::start()
{
    //TODO
    serialPort = new QSerialPort();

    //findComPortByDeviceName();

    serialPort->setPortName(arduinoConfig.serialPort);
    auto serialPortBaudRate = QSerialPort::Baud9600;
    serialPort->setBaudRate(serialPortBaudRate);

    if (!serialPort->open(QIODevice::ReadOnly))
    {
        qDebug()<<"serialPort opening error";
    }
    else
    {
        connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortErro)));

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        timer->start(taskTimerMills);
    }
}

void ArduinoComponent::onReadyRead()
{
    readData.append(serialPort->readAll());
}

void ArduinoComponent::onReadError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError)
    {

    }
}
void ArduinoComponent::onUpdate()
{
    if (!readData.isEmpty())
    {

    }
    else
    {

    }
}

ArduinoConfig ArduinoComponent::config() const
{
    return arduinoConfig;
}

void ArduinoComponent::setQmlContext(QQmlContext* value)
{
    BaseComponent::setQmlContext(value);
    qmlContext->setContextProperty("arduino", this);
}

void ArduinoComponent::setConnected(bool value)
{
    _connected = value;
    emit connectedChanged();
}

bool ArduinoComponent::connected() const
{
    return _connected;
}

bool ArduinoComponent::isHealthy()
{
    return true;
}
