#include "TaskCreator.h"
#include "core/game/GameTask.h"

TaskCreator::TaskCreator(QObject *parent) : QObject(parent)
{


}

 QMap<int, QSharedPointer<GameTask>> TaskCreator::create(UserData* user)
{
   auto gameProgress = user->getGameProgess();
   auto games = gameProgress->getGames();
   QMap<int, QSharedPointer<GameTask>> gameTasks;

   for(OneGameData oneGameData: gameProgress->getGames())
   {
       if(!oneGameData.complete())
       {
           auto id = oneGameData.getId();
           QSharedPointer<GameTask> gameTask(new GameTask(oneGameData.getPath(), oneGameData.getDifficult()));
           gameTasks.insert(id, gameTask);
       }
   }

   return gameTasks;
}
