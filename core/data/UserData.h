#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <qDebug>
#include <QQmlContext>
#include "core/game/GameProgress.h"

struct BaseUserInfo
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString surname MEMBER surname)
    Q_PROPERTY(QString email MEMBER email)
    Q_PROPERTY(QString phone MEMBER phone)
   // Q_PROPERTY(int confirmed MEMBER confirmed)
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


struct UserObject
{
    BaseUserInfo baseUserInfo;
};


class UserData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString surname READ surname WRITE setSurname NOTIFY surnameChanged)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool exist READ exist WRITE setExist NOTIFY existChanged)
    Q_PROPERTY(bool firstTime READ firstTime WRITE setFirstTime NOTIFY firstTimeChanged)
    Q_PROPERTY(bool finished READ finished WRITE setFinished NOTIFY finishedChanged)
    Q_PROPERTY(bool waitEnoughToPlay READ waitEnoughToPlay WRITE setWaitEnoughToPlay NOTIFY waitEnoughToPlayChanged)
    Q_PROPERTY(bool playingOnAnother READ playingOnAnother WRITE setPlayingOnAnother NOTIFY playingOnAnotherChanged)
    Q_PROPERTY(QVariantList prizes READ prizes WRITE setPrizes NOTIFY prizesChanged)

    Q_PROPERTY(int currentGameId READ currentGameId WRITE setCurrentGameId NOTIFY currentGameIdChanged)
    Q_PROPERTY(int gamesCount READ gamesCount WRITE setGamesCount NOTIFY gamesCountChanged)
    Q_PROPERTY(int gamesCompleteCount READ gamesCompleteCount WRITE setGamesCompleteCount NOTIFY gamesCompleteCountChanged)
    Q_PROPERTY(float cleanGameTime READ cleanGameTime WRITE setCleanGameTime NOTIFY cleanGameTimeChanged)


    Q_ENUMS(UserState)
    Q_ENUMS(LoginState)

public:
    explicit UserData(QObject *parent = nullptr);
    virtual ~UserData();

    enum class UserState
    {
        None,
        CanPlay,
        DoesntExists,
        Finished,
        WasRecently,
        YouArePlaying
    };

    enum class LoginState
    {
        Login,
        Logout,
        Error
    };

    const int maxPrizesCount = 2;

    QString name() const;
    QString surname() const;
    int id() const;
    bool exist() const;
    bool firstTime() const;
    bool finished() const;
    QVariantList prizes() const;
    bool waitEnoughToPlay() const;
    bool playingOnAnother() const;

    void setName(const QString& value);
    void setSurname(const QString& value);
    void setId(int value);
    void setExist(bool value);
    void setFirstTime(bool value);
    void setFinished(bool value);
    void setPrizes(const QVariantList& value);
    void setWaitEnoughToPlay(bool value);
    void setPlayingOnAnother(bool value);

    void setQmlContext(QQmlContext* value);
    void setGameProgess(const GameProgress& value);
    void clearData();


    void parse(const QString& userObject);
    void setNewUserData(const UserObject& userObject);
    void setUserDoesntExist();



    GameProgress getGameProgess() const;
    OneGameData getCurrentGameData() const;
    void currentGameCompleted(int time);
    bool hasGames() const;

    void setUserState(UserState value);
    void setLoginState(LoginState value);
    QString getStringState() const;

private:
    QString _name = "Unknown";
    QString _surname = "Unknown";
    int _id = -1;

    bool _exist = false;
    bool _firstTime = false;
    bool _finished = false;
    QVariantList _prizes;
    bool _waitEnoughToPlay = false;
    bool _playingOnAnother = false;

    QQmlContext* qmlContext;

    GameProgress gameProgress;
    UserState userState;
    LoginState loginState = LoginState::Logout;

    int _currentGameId = 0;
    int _gamesCount = 0;
    int _gamesCompleteCount = 0;
    float _cleanGameTime = 0.0f;

    void updateGameProgressData();

    void setCurrentGameId(int stage);
    int currentGameId() const;

    void setGamesCount(int count);
    int gamesCount() const;

    void setGamesCompleteCount(int count);
    int gamesCompleteCount() const;

    void setCleanGameTime(float count);
    float cleanGameTime() const;

signals:
    void nameChanged();
    void surnameChanged();
    void idChanged();
    void existChanged();
    void firstTimeChanged();
    void waitEnoughToPlayChanged();
    void finishedChanged();
    void prizesChanged();
    void playingOnAnotherChanged();

    void userStateChanged(UserData::UserState userState);
    void loginStateChanged(UserData::LoginState loginState);

signals:
    void currentGameIdChanged();
    void gamesCountChanged();
    void gamesCompleteCountChanged();
    void cleanGameTimeChanged();
};

#endif // USERDATA_H
