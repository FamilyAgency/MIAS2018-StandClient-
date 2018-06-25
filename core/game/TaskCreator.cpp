#include "TaskCreator.h"
#include "core/game/GameTask.h"

TaskCreator::TaskCreator(QObject *parent) : QObject(parent)
{


}

QList<GameTask*> TaskCreator::create()
{
    VelocityCalculator velocitycalculator;
    velocitycalculator.setLimits(0, 3, 60);

    QVector<QPointF> path;
    QPointF point1 = QPointF(388, 88);
    QPointF point2 = QPointF(621, 71 );
    QPointF point3 = QPointF(970, 114);
    QPointF point4 = QPointF(223, 222);
    QPointF point5 = QPointF(347, 243);
    QPointF point6 = QPointF(467, 264);
    QPointF point7 = QPointF(690, 300);
    QPointF point8 = QPointF(987, 207);
    QPointF point9 = QPointF(218, 422);
    QPointF point10 = QPointF(511, 357);
    QPointF point11 = QPointF(969, 389);
    QPointF point12 = QPointF(1152, 379);
    QPointF point13 = QPointF(315, 537);
    QPointF point14 = QPointF(573, 417);
    QPointF point15 = QPointF(666, 500);
    QPointF point16 = QPointF(735, 458);
    QPointF point17 = QPointF(917, 495);
    QPointF point18 = QPointF(913, 570);
    QPointF point19 = QPointF(1144, 616);
    QPointF point20 = QPointF(1002, 316);

    QList<GameTask*> gameTasks;

    //penta
    //path.clear();
   // path<<QPointF(150, 125)<<QPointF(260, 210)<<QPointF(125, 210)<<QPointF(235, 125)<<QPointF(194, 260)<<QPointF(150, 125);
   // velocitycalculator.setLimits(0, 3.5, 40);
  //  gameTasks.append(new GameTask(path, velocitycalculator));



    //PATH1
    path.clear();
    path<<point4<<point6<<point10<<point7<<point16<<point17;
    velocitycalculator.setLimits(0, 3.5, 40);
    gameTasks.append(new GameTask(path, velocitycalculator));

    //PATH2
    path.clear();
    path<<point17<<point20<<point3<<point2;
    velocitycalculator.setLimits(0, 3.3, 45);
    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH3
//    path.clear();
//    velocitycalculator.setLimits(0, 3, 60);
//    path<<point2<<point1<<point6<<point5<<point9;
//    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH4
//    path.clear();
//    velocitycalculator.setLimits(0, 2, 65);
//    path<<point9<<point13<<point10<<point14<<point15<<point16<<point17<<point18<<point19;
//    gameTasks.append(new GameTask(path, velocitycalculator));

//    //PATH5
//    path.clear();
//    velocitycalculator.setLimits(0, 3, 70);
//    path<<point19<<point12<<point11<<point20<<point8<<point10<<point1;
//    gameTasks.append(new GameTask(path, velocitycalculator));

    return gameTasks;
}
