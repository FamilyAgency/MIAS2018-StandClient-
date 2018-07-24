#ifndef MINDWAVECOMPONENTSERIAL_H
#define MINDWAVECOMPONENTSERIAL_H

#include  "components/mindwave/MindwaveComponentBase.h"

class MindwaveComponentSerial  : public MindwaveComponentBase
{
    Q_OBJECT
public:
    explicit MindwaveComponentSerial(QObject *parent = nullptr);    
    ~MindwaveComponentSerial();
};

#endif // MINDWAVECOMPONENTSERIAL_H
