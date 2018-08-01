#include "InstructionModule.h"

InstructionModule::InstructionModule(QObject *parent) : BaseModule(parent)
{

}

InstructionModule::~InstructionModule()
{

}

void InstructionModule::setConfig(ConfigPtr config)
{

}

void InstructionModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("instructionModule", this);
}

void InstructionModule::start()
{
    qDebug()<<"======================= InstructionModule START =======================";

}

void InstructionModule::stop()
{
    qDebug()<<"======================= InstructionModule STOP =======================";

}

void InstructionModule::rouletteButtonClick()
{
    emit userStartRoulette();
}

QString InstructionModule::getName() const
{
    return "Instructions location";
}

