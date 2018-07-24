#ifndef MINDWAVEREADERTCP_H
#define MINDWAVEREADERTCP_H

#include <QObject>
#include "components/mindwave/MindwaveReaderBase.h"

class MindwaveReaderTCP : public MindwaveReaderBase
{
    Q_OBJECT
public:
    explicit MindwaveReaderTCP(QObject *parent = nullptr);
    virtual ~MindwaveReaderTCP();

    virtual void setConfig(const MindwaveConfig& value) override;
    virtual void start() override;

protected slots:
    virtual void onConnectionSuccess();
};

#endif // MINDWAVEREADERTCP_H
