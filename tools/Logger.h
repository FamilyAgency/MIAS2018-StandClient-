#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>

class Logger : public QObject
{
   Q_OBJECT

public:
    enum class LogType
    {
        Verbose,
        Warning,
        Error
    };

    Logger();
    void log(const QString& msg, LogType type = LogType::Verbose);

signals:
    void logToOutputConsole(const QString& msg, const QString& color = "black");

private:
    struct LogTypeInfo
    {
        LogTypeInfo(){}
        LogTypeInfo(const QString& color)
        {
            this->color = color;
        }

        QString color;
    };

    QString getColorByType(LogType type);
    QMap<LogType, LogTypeInfo> logData;

};

#endif // LOGGER_H
