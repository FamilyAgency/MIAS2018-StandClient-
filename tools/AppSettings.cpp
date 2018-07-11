#include "AppSettings.h"
#include <windows.h>
#include <QLocale.h>
#include <QDate>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QSettings>

AppSettings::AppSettings(QObject *parent) : QObject(parent)
{

}

void AppSettings::init()
{
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    _set_error_mode (_OUT_TO_STDERR);
}




