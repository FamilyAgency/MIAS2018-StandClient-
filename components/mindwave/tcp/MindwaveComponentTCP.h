#ifndef MINDWAVECOMPONENTTCP_H
#define MINDWAVECOMPONENTTCP_H

#include <QObject>
#include  "components/mindwave/MindwaveComponentBase.h"

class MindwaveComponentTCP : public MindwaveComponentBase
{
    Q_OBJECT
public:
    explicit MindwaveComponentTCP(QObject *parent = nullptr);
    virtual ~MindwaveComponentTCP();

private slots:

   // virtual void onDataRecieve(const QString& data) override;
};

#endif // MINDWAVECOMPONENTTCP_H
