#ifndef MINDWAVEPARSERTCP_H
#define MINDWAVEPARSERTCP_H

#include <QObject>
#include "components/mindwave/MindwaveParserBase.h"

class MindwaveParserTCP : public MindwaveParserBase
{
    Q_OBJECT
public:
    explicit MindwaveParserTCP(QObject *parent = nullptr);
    virtual MindwaveData parse(const QString& data) override;

protected:
    virtual MindwaveData parseOneDataChunck(const QString& data) override;

private:
    int remapPoorSignalLevel(int signalValue) const;

signals:
     void scanningInfo(int signalValue, const QString& status);

};

#endif // MINDWAVEPARSERTCP_H
