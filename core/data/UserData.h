#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <qDebug>
#include <QQmlContext>
#include "core/data/OneStageData.h"
#include "config/Config.h"

struct BaseUserInfo
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString surname MEMBER surname)
    Q_PROPERTY(QString email MEMBER email)
    Q_PROPERTY(QString phone MEMBER phone)
    Q_PROPERTY(int test MEMBER test)

public:
    int id = 0;
    QString name = "";
    QString surname = "";
    QString email = "";
    QString phone = "";
    int test = 0;
    int confirmed = 0;

    Q_INVOKABLE bool isPinConfirmed() const
    {
        return confirmed == 1;
    }

    Q_INVOKABLE int getPinToConfirm() const
    {
        return confirmed;
    }

    void print()
    {
        qDebug()<<"===== User Info =====";
        qDebug()<<"id = "<<id;
        qDebug()<<"name = "<<name;
        qDebug()<<"surname = "<<surname;
        qDebug()<<"email = "<<email;
        qDebug()<<"phone = "<<phone;
        qDebug()<<"confirmed = "<<confirmed;
        qDebug()<<"test = "<<test;
        qDebug()<<"====================";
    }

    void clear()
    {
        id = 0;
        name = "";
        surname = "";
        email = "";
        phone = "";
        confirmed = 0;
        test = 0;
    }
};
Q_DECLARE_METATYPE(BaseUserInfo)

struct PrizesUserData
{
private:
    Q_PROPERTY(bool prize1 MEMBER prize1)
    Q_PROPERTY(bool prize2 MEMBER prize2)
    Q_GADGET

public:
    bool prize1 = false;
    bool prize2 = false;
};
Q_DECLARE_METATYPE(PrizesUserData)

struct GameUserData
{
private:
    Q_GADGET
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(QVariantList stageTimes MEMBER stageTimes)
    Q_PROPERTY(float superGameTime MEMBER superGameTime)

public:
    QVector<OneStageData> stages;
    int currentGameId;
    int cleanGameTime;
    OneStageData currentStage;
    bool _hasGames = false;
    QString description;
    QVariantList stageTimes;

    float superGameTime = 0.0;

    GameUserData()
    {
        stageTimes.push_back(0.0f);
        stageTimes.push_back(0.0f);
        stageTimes.push_back(0.0f);
    }

    void setupConfigGameData(const StandOneGameConfig& game)
    {
        stages.clear();
        stageTimes.clear();

        description = game.description;
        qDebug()<<"description   "<<description;

        for(int i = 0; i < game.stages.size(); i++)
        {
            OneStageData oneGameData;
            oneGameData.setId(i + 1);
            oneGameData.setComplete(false);
            oneGameData.setTime(0.0f);
            oneGameData.setPath(game.stages[i].path);
            oneGameData.setDifficult(VelocityCalculator(2, 3, 60));
            oneGameData.setAdvantage(game.stages[i].advantage);
            stages.push_back(oneGameData);
            stageTimes.push_back(0.0f);
        }

        _hasGames = true;
    }

    void setCurrentGameId(int id)
    {
        currentGameId = id;
        currentStage = stages[id - 1];
    }

    OneStageData getCurrentStage() const
    {
        return currentStage;
    }

    void currentStageCompleted(int time)
    {
        const float toSeconds = 1/1000.0f;
        stageTimes[currentGameId - 1] = time * toSeconds;

        currentStage.setTime(time);
        qDebug()<<"Current game id "<<currentGameId<<stages.size();
        if(currentGameId + 1 <= stages.size())
        {
            _hasGames = true;
            setCurrentGameId(currentGameId + 1);
        }
        else
        {
            _hasGames = false;
        }
    }

    bool hasStages() const
    {
        return _hasGames;
    }
};
Q_DECLARE_METATYPE(GameUserData)

struct UserObject
{
    BaseUserInfo baseUserInfo;
    PrizesUserData prizesUserData;
    GameUserData gameUserData;
};

class UserData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BaseUserInfo baseUserData READ baseUserData WRITE setBaseUserData NOTIFY baseUserDataChanged)
    Q_PROPERTY(PrizesUserData prizesUserData READ prizesUserData WRITE setPrizesUserData NOTIFY prizesUserDataChanged)
    Q_PROPERTY(GameUserData gameUserData READ gameUserData WRITE setGameUserData NOTIFY gameUserDataChanged)

    Q_ENUMS(CantPlayReason)

public:
    explicit UserData(QObject *parent = nullptr);
    virtual ~UserData();

    enum class CantPlayReason
    {
        None,
        WasRecently,
        YouArePlaying,
        Finished
    };  

    void setBaseUserData(const BaseUserInfo& value);
    BaseUserInfo baseUserData() const;

    void setPrizesUserData(const PrizesUserData& value);
    PrizesUserData prizesUserData() const;

    void setGameUserData(const GameUserData& value);
    GameUserData gameUserData() const;

    OneStageData getCurrentStage() const;
    void currentStageCompleted(int time);

    bool hasStages() const;

    void setQmlContext(QQmlContext* value);
    void setConfig(ConfigPtr value);

    void setGameConfig(StandGamesConfig config);
    void clearData();

    void setNewUserData(const UserObject& userObject);
    void setUserDoesntExist();

    void setGameCategory(int id);

    Q_INVOKABLE CantPlayReason getReasonCantPlay() const;
    bool canPlay() const;
    bool allPrizesGot() const;
    bool wasRecently() const;
    bool playingOnAnotherStand() const;

    SuperGameConfig getSuperGameData() const;

private:
    BaseUserInfo _baseUserData;
    PrizesUserData _prizesUserData;
    GameUserData _gameUserData;

    StandGamesConfig _gameConfig;
    SuperGameConfig superGameConfig;

    QQmlContext* qmlContext;

    bool _canPlay = false;
    CantPlayReason cantPlayReason;

    void checkCanUserPlay();

signals:
    void baseUserDataChanged();
    void prizesUserDataChanged();
    void gameUserDataChanged();
    void userCantStartReason(CantPlayReason reason);

};

#endif // USERDATA_H
