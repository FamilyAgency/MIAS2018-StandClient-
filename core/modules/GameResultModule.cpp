#include "GameResultModule.h"

GameResultModule::GameResultModule(QObject *parent) : BaseModule(parent)
{

}

GameResultModule::~GameResultModule()
{

}

void GameResultModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("gameResultModule", this);
}

void GameResultModule::start()
{
    qDebug()<<"======================= Game Result Module START =======================";

}

void GameResultModule::stop()
{
    qDebug()<<"======================= Game Result Module STOP =======================";

}

void GameResultModule::superGameAcceptedButtonClick()
{
    emit superGameAccepted();
}

void GameResultModule::superGameRejectedButtonClick()
{
    emit superGameRejected();
}

QString GameResultModule::getName() const
{
    return "Game Result location";
}
