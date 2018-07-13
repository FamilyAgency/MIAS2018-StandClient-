#include "AppSettings.h"
#include <windows.h>
#include <QLocale.h>
#include <QDate>
#include <QString>
#include <QDebug>
#include <QTextCodec>
#include <QSettings>

#include <QTranslator>
#include <QLibraryInfo>
#include <QTextCodec>

AppSettings::AppSettings(QObject *parent) : QObject(parent)
{

}

void AppSettings::init()
{
    SetErrorMode(SEM_NOGPFAULTERRORBOX);
    _set_error_mode (_OUT_TO_STDERR);


    //    QTranslator qtTranslator;
    //    qtTranslator.load("qt_" + QLocale::system().name(),
    //                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    //    app.installTranslator(&qtTranslator);

    //    QTranslator myappTranslator;
    //    myappTranslator.load("myapp_" + QLocale::system().name());
    //    app.installTranslator(&myappTranslator);

    //    qDebug()<<"qt_" + QLocale::system().name();

//        QTextCodec* defaultTextCodec = new QTextCodec::codecForName("Windows1251");
//        QTextDecoder *decoder = new QTextDecoder(defaultTextCodec);
//        QString str = decoder->toUnicode("Открыть рисунок");
//        qDebug()<<"str_" + str;
//QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
//qDebug << QString::fromUtf8("Привет!").toLocal8Bit().data();
///    SetConsoleCP(1251);
//   SetConsoleOutputCP(1251);

}






