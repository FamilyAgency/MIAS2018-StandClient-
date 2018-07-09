#ifndef INSTRUCTIONMODULE_H
#define INSTRUCTIONMODULE_H

#include <QObject>
#include "BaseModule.h"

class InstructionModule : public BaseModule
{
    Q_OBJECT
public:
    explicit InstructionModule(QObject *parent = nullptr);    
    virtual ~InstructionModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;

    virtual QString getName() const override;
};

#endif // INSTRUCTIONMODULE_H
