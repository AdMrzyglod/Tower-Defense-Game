#ifndef TOWER_H
#define TOWER_H


#include "bullet.h"
#include "map.h"
#include "enemy.h"
#include "Direction.h"
#include <QGraphicsPixmapItem>

class TowerPlace;

class Tower: public QGraphicsPixmapItem
{
public:
    Tower(Map* map, std::pair<int, int> position,TowerPlace* towerPlace,int level);

    ~Tower();

    void shot();

    int getLevel(){
        return level;
    }

    double getDistance(std::pair<int,int> point1,std::pair<int,int> point2);



private:
    Map* map;
    TowerPlace* towerPlace;
    std::pair<int,int> center;
    int pixelRadius;
    int rateOfFire;
    int level;
    int counter;
    bool afterShot;
    bool enemyInRange(Enemy* enemy);
    bool pointInRange(std::pair<int,int> point);

    void sendBulletToPoint(std::pair<int,int> point);
};

#endif // TOWER_H
