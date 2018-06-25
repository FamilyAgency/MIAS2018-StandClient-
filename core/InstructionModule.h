#ifndef INSTRUCTIONMODULE_H
#define INSTRUCTIONMODULE_H

#include <QObject>
#include "BaseModule.h"

class InstructionModule : public BaseModule
{
    Q_OBJECT
public:
    explicit InstructionModule(QObject *parent = nullptr);

    virtual void setConfig(Config* config) override;
    void setQmlContext(QQmlContext* qmlContext) override;
    virtual void start() override;
    virtual void stop() override;

signals:

public slots:
};

#endif // INSTRUCTIONMODULE_H
