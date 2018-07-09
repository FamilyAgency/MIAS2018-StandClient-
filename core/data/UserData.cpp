#include "UserData.h"
#include <QQmlEngine>
#include <QJsonDocument.h>
#include <QJsonObject.h>
#include <QJsonArray.h>

UserData::UserData(QObject *parent) : QObject(parent)
{
    QVariantList prizes;
    prizes.append(false);
    prizes.append(false);
    setPrizes(prizes);

    gameProgress = new GameProgress();
    gameProgress->setCurrentGameId(1);
    gameProgress->setGamesCount(0);
    gameProgress->setGamesCompleteCount(0);
}

UserData::~UserData()
{
    if(gameProgress)
    {
        delete gameProgress;
    }
}

void UserData::setQmlContext(QQmlContext* value)
{
    qmlContext = value;
    qmlContext->setContextProperty("userData", this);
    gameProgress->setQmlContext(qmlContext);
}

void UserData::setUserState(UserState value)
{
    userState = value;
    emit userStateChanged(value);
}
void UserData::setLoginState(LoginState value)
{
    loginState = value;
    emit loginStateChanged(value);
}

QString UserData::getStringState() const
{
    switch(loginState)
    {
    case LoginState::Login: return "User login";
    case LoginState::Logout: return "User logout";
    }
    return "undefined";
}

QVariantList UserData::prizes() const
{
    return _prizes;
}

void UserData::setPrizes(const QVariantList& value)
{
    _prizes = value;
    emit prizesChanged();
}

QString UserData::name() const
{
    return _name;
}

QString UserData::surname() const
{
    return _surname;
}

int UserData::id() const
{
    return _id;
}

bool UserData::exist() const
{
    return _exist;
}

bool UserData::firstTime() const
{
    return _firstTime;
}

bool UserData::finished() const
{
    return _finished;
}

bool UserData::waitEnoughToPlay() const
{
    return _waitEnoughToPlay;
}

bool UserData::playingOnAnother() const
{
    return _playingOnAnother;
}

void UserData::setName(const QString& value)
{
    _name = value;
    emit nameChanged();
}

void UserData::setSurname(const QString& value)
{
    _surname = value;
    emit surnameChanged();
}

void UserData::setId(int value)
{
    _id = value;
    emit idChanged();
}

void UserData::setExist(bool value)
{
    _exist = value;
    emit existChanged();
}

void UserData::setFirstTime(bool value)
{
    _firstTime = value;
    emit firstTimeChanged();
}

void UserData::setFinished(bool value)
{
    _finished = value;
    emit finishedChanged();
}

void UserData::setWaitEnoughToPlay(bool value)
{
    _waitEnoughToPlay = value;
    emit waitEnoughToPlayChanged();
}

void UserData::setPlayingOnAnother(bool value)
{
    _playingOnAnother = value;
    emit playingOnAnotherChanged();
}

void UserData::setGameProgess(GameProgress* value)
{
    gameProgress = value;
}

GameProgress* UserData::getGameProgess()
{
    return gameProgress;
}

OneGameData UserData::getCurrentGameData() const
{
    return gameProgress->getCurrentGameData();
}

void UserData::currentGameCompleted(int time)
{
    gameProgress->currentGameCompleted(time);
}

bool UserData::hasGames() const
{
    return gameProgress->hasGames();
}

void UserData::clearData()
{
    gameProgress->setCleanTime(0.0f);
    gameProgress->setCurrentGameId(0);
    gameProgress->setGamesCount(0);
    gameProgress->setGamesCompleteCount(0);
}

void UserData::parse(const QString& userObject)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(userObject.toUtf8());
    QJsonObject jsonObj   = jsonDoc.object();

    setName(jsonObj["name"].toString());
    setSurname(jsonObj["surname"].toString());
    setId(jsonObj["id"].toInt());
    setFirstTime(true);
    setFinished(false);
    setExist(jsonObj["exist"].toBool());
    setWaitEnoughToPlay(jsonObj["waitEnoughToPlay"].toBool());
    setPlayingOnAnother(jsonObj["playingOnAnother"].toBool());
    setFinished(jsonObj["finished"].toBool());

    QVariantList prizes;
    prizes.append(true);
    prizes.append(false);
    setPrizes(prizes);

   // GameProgress* gameProgress = createGamesOnStage1();
   // userData->setGameProgess(gameProgress);

    if(!exist())
    {
        setUserState(UserData::UserState::DoesntExists);
        return;
    }

    if(!waitEnoughToPlay())
    {
        setUserState(UserData::UserState::WasRecently);
        return;
    }

    if(playingOnAnother())
    {
        setUserState(UserData::UserState::YouArePlaying);
        return;
    }

    if(finished())
    {
        setUserState(UserData::UserState::Finished);
        return;
    }

    setUserState(UserData::UserState::CanPlay);
    setLoginState(UserData::LoginState::Login);
}

