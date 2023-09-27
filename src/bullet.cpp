#include "bullet.h"
#include "map.h"
#include <cmath>
#include "enemy.h"
#include "game.h"

Bullet::Bullet(std::pair<int,int> startPoint,std::pair<int,int> endPoint,int level,Map* map)
{
    this->map=map;
    this->level = level;
    this->startPoint = startPoint;
    this->endPoint = endPoint;
    this->speed=this->map->getGame()-> getConfig()->getTowerDetails()->at(level-1).bulletSpeed;
    this->damage=this->map->getGame()-> getConfig()->getTowerDetails()->at(level-1).bulletDamage;
    float time = sqrt(pow(startPoint.first - endPoint.first, 2) + pow(startPoint.second - endPoint.second, 2))/speed;
    this->shift=std::make_pair((-startPoint.first+endPoint.first)/time,(-startPoint.second+endPoint.second)/time);
    this->bulletTime = 0;

    setPixmap(QPixmap(":/images/"+this->map->getGame()-> getConfig()->getTowerDetails()->at(level-1).bulletImage).scaled(map->getSquareSize()/2,map->getSquareSize()*3/4));
    setTransformOriginPoint(boundingRect().center());
    setRotation(90+rotation()+ std::atan2(-startPoint.second+endPoint.second,-startPoint.first+endPoint.first)*180/M_PI);

    setPos(startPoint.first,startPoint.second);
    this->map->addBullet(this);
}

void Bullet::move(){
    setPos(std::ceil(this->startPoint.first+this->shift.first*this->bulletTime),std::ceil(this->startPoint.second+this->shift.second*this->bulletTime));
    this->bulletTime++;
}


bool Bullet::isHit(Enemy* enemy){

    QPainterPath rect;
    rect.addRect(x(),y(),this->boundingRect().width(),this->boundingRect().height());

    QPainterPath circle;
    circle.addEllipse(enemy->getCenter().first,enemy->getCenter().second,enemy->getRadius(),enemy->getRadius());

    if(rect.intersects(circle)){
        return true;
    }

    return false;
}



Bullet::~Bullet(){

    this->speed=0;
    this->damage=0;
    this->level=0;
    this->bulletTime=0;
    this->map=nullptr;
}

















