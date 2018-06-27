#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <QObject>
#include <QString>
#include "BaseModule.h"
#include "components/MindwaveComponent.h"
#include "core/game/GameTaskManager.h"
#include "core/UserData.h"
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
    void setMindwave(MindwaveComponent* value);
    virtual QString getName() const override;

    void setUser(UserData* value);

private:
    MindwaveComponent* mindWaveComponent;
    QScopedPointer<GameTaskManager> gameTaskManager;
    GameSession* gameSession;
    UserData* currentUser;

private slots:
    void onTaskComleteEvent(int completionTime);
    void onAllTaskComleteEvent();

signals:
    void allTaskComleteEvent();
};

#endif // GAMEMODULE_H
