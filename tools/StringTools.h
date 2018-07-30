#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H
#include <QChar.h>
#include <QString.h>
#include <QMap.h>

class StringTools
{
public:
    StringTools();

    QChar toCyrConverter(const QString& unicode);
    QString convertUnicodeToCyrillic(const QByteArray& unicodeBytes);

private:
   QMap<QString, QString> unicodeTable;
};

#endif // STRINGTOOLS_H
