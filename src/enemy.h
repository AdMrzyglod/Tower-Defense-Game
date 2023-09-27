#ifndef ENEMY_H
#define ENEMY_H

#include "Direction.h"
#include "map.h"
#include <QGraphicsPixmapItem>


class Enemy: public QGraphicsPixmapItem
{
public:
    Enemy(int level,Map* map);

    Enemy(const Enemy& other)
    {
        this->map = other.map;
        this->speed = getRadius();
        this->pointIndex = other.pointIndex;
        this->direction = other.direction;
        setPos(other.pos());
    }

    ~Enemy();

    void move();

    int testMove();

    std::pair<int,int> getCenter();

    int getRadius();

    Direction getDirection(){
        return this->direction;
    }

    int getLevel(){
        return level;
    }

    int getSpeed(){
        return this->speed;
    }

    void updateHealth(int points){
        this->health+=points;
    }

    bool healthAboveZero(){
        return this->health>0;
    }


private:
    int level;
    int health;
    int speed;
    Direction direction;
    Map* map;
    int pointIndex;
};

#endif // ENEMY_H
