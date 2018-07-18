#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <QObject>
#include <QString>
#include "BaseModule.h"
#include "components/MindwaveComponent.h"
#include "core/game/GameTaskManager.h"
#include "core/data/UserData.h"
#include "core/GameSession.h"

class GameModule : public BaseModule
{
    Q_OBJECT
public:
    explicit GameModule(QObject *parent = nullptr);
    virtual ~GameModule();

    Q_INVOKABLE void continueGame();

    virtual void setQmlContext(QQmlContext* value) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;

    virtual QString getName() const override;

    void setGameSession(QSharedPointer<GameSession> value);
    void setMindwave(QSharedPointer<MindwaveComponent> value);
    void setUser(QSharedPointer<UserData> value);

private:
    QSharedPointer<MindwaveComponent> mindWaveComponent;
    QScopedPointer<GameTaskManager> gameTaskManager;
    QSharedPointer<GameSession> gameSession;
    QSharedPointer<UserData> currentUser;

private slots:
    void onTaskComleteEvent(int completionTime);
    void onAllTaskComleteEvent();

signals:
    void allTaskComleteEvent();
    void taskComleteEvent(const QString& title, const QString& description);
};

#endif // GAMEMODULE_H
