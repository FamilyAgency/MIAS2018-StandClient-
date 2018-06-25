#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "components/MindwaveComponent.h"
#include "core/game/GameTaskManager.h"
#include "GameSession.h"

class GameModule : public BaseModule
{
    Q_OBJECT
public:
    GameModule();

    virtual void setConfig(Config* config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual void setQmlContext(QQmlContext* value) override;
    void setGameSession(GameSession* gameSession);

private:
    QScopedPointer<MindwaveComponent>  mindWave;
    QScopedPointer<GameTaskManager> gameTaskManager;
    GameSession* gameSession;

private slots:
    void onTaskComleteEvent(int completionTime);
    void onAllTaskComleteEvent();

signals:
    void allTaskComleteEvent();
};

#endif // GAMEMODULE_H
