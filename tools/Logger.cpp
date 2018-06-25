#include "Logger.h"

Logger::Logger()
{
    logData.insert(LogType::Verbose, LogTypeInfo("black"));
    logData.insert(LogType::Warning, LogTypeInfo("yellow"));
    logData.insert(LogType::Error, LogTypeInfo("red"));
}

void Logger::log(const QString& msg, LogType type)
{
    QString color = getColorByType(type);
    qDebug()<<msg;
    emit logToOutputConsole(msg, color);
}

QString Logger::getColorByType(LogType type)
{
    if(logData.contains(type))
    {
        return logData[type].color;
    }

    return "black";
}
