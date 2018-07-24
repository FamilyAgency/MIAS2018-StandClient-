#ifndef MINDWAVEPARSERTCP_H
#define MINDWAVEPARSERTCP_H

#include "components/mindwave/MindwaveParserBase.h"

class MindwaveParserTCP : public MindwaveParserBase
{
    Q_OBJECT
public:
    explicit MindwaveParserTCP(QObject *parent = nullptr);
    virtual void parse(const QString& data) override;

protected:
    virtual MindwaveData parseOneDataChunck(const QString& data);
};

#endif // MINDWAVEPARSERTCP_H
