#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class Map;

class Enemy;

class Bullet: public QGraphicsPixmapItem
{
public:
    Bullet(std::pair<int,int> startPoint,std::pair<int,int> endPoint,int level,Map* map);

    ~Bullet();

    void move();

    bool isHit(Enemy* enemy);

    std::pair<int,int> getPosition(){
        return std::make_pair(x(),y());
    }

    int getDamage(){
        return this->damage;
    }
    int getLevel(){
        return level;
    }

private:
    std::pair<int,int> startPoint;
    std::pair<int,int> endPoint;
    int speed;
    int damage;
    std::pair<float,float> shift;
    int bulletTime;
    int level;
    Map* map;

};

#endif // BULLET_H
