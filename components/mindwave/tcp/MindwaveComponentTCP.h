#ifndef MINDWAVECOMPONENTTCP_H
#define MINDWAVECOMPONENTTCP_H

#include  "components/mindwave/MindwaveComponentBase.h"

class MindwaveComponentTCP : public MindwaveComponentBase
{
    Q_OBJECT
public:
    explicit MindwaveComponentTCP(QObject *parent = nullptr);
    virtual ~MindwaveComponentTCP();
};

#endif // MINDWAVECOMPONENTTCP_H
