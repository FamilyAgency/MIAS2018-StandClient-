#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>

class AppSettings : public QObject
{
    Q_OBJECT
public:
    explicit AppSettings(QObject *parent = nullptr);

    void init();
};

#endif // APPSETTINGS_H
