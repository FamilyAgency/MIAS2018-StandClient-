#include "TaskCreator.h"
#include "core/game/GameTask.h"

TaskCreator::TaskCreator(QObject *parent) : QObject(parent)
{


}

QList<QSharedPointer<GameTask>> TaskCreator::create(UserData* user)
{
   auto gameProgress = user->getGameProgess();
   auto games = gameProgress->getGames();

   QList<QSharedPointer<GameTask>> gameTasks;
   for(auto game: games)
   {
       QSharedPointer<GameTask> gameTask(new GameTask(game.getPath(), game.getDifficult()));
       gameTasks.push_back(gameTask);
   }

   return gameTasks;
}
