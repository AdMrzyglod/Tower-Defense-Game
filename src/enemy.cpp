#include "enemy.h"
#include "game.h"


Enemy::Enemy(int level,Map* map)
{
    this->map=map;
    setPixmap(QPixmap(":/images/"+this->map->getGame()->getConfig()->getEnemyDetails()->at(level).image).scaled(map->getSquareSize(),map->getSquareSize()));
    setTransformOriginPoint(boundingRect().center());
    setRotation(-90);
    this->level = level;
    this->health = map->getGame()->getConfig()->getEnemyDetails()->at(level).health;
    this->speed= map->getGame()->getConfig()->getEnemyDetails()->at(level).speed;
    this->pointIndex=1;
    this->direction=getPointsDirection(this->map->roadPoint(this->pointIndex-1),this->map->roadPoint(this->pointIndex));
    setPos(this->map->roadPoint(this->pointIndex-1).x(),this->map->roadPoint(this->pointIndex-1).y());
}

void Enemy::move()
{
    QPoint currentPos = this->pos().toPoint();
    QPoint targetPos = this->map->roadPoint(this->pointIndex);

    Direction newDirection = getPointsDirection(currentPos, targetPos);

    if (newDirection != this->direction) {
        this->pointIndex++;
        if(this->pointIndex>=this->map->getRoadPoints().size()){
            this->map->addEnemyToDelete(this);
            this->map->getGame()->updateHealth(-this->map->getGame()->getConfig()->getEnemyDetails()->at(level).damageFromEnemy);
            return;
        }
        Direction previous = this->direction;
        this->direction = getPointsDirection(this->map->roadPoint(this->pointIndex-1), this->map->roadPoint(this->pointIndex));
        setPixmap(pixmap().transformed(QTransform().rotate(nextDirection(previous)==this->direction ? 90 : -90)));
    }

    switch (this->direction) {
    case Direction::North:
        currentPos.setY(std::max(currentPos.y() - this->speed,this->map->roadPoint(this->pointIndex).y()));
        break;
    case Direction::South:
        currentPos.setY(std::min(currentPos.y() + this->speed,this->map->roadPoint(this->pointIndex).y()));
        break;
    case Direction::East:
        currentPos.setX(std::min(currentPos.x() + this->speed,this->map->roadPoint(this->pointIndex).x()));
        break;
    case Direction::West:
        currentPos.setX(std::max(currentPos.x() - this->speed,this->map->roadPoint(this->pointIndex).x()));
        break;
    default:
        break;
    }

    this->setPos(currentPos);
}



int Enemy::testMove()
{

    if(this->pointIndex>=this->map->getRoadPoints().size()){
        return 0;
    }


    QPoint currentPos = this->pos().toPoint();
    QPoint targetPos = this->map->roadPoint(this->pointIndex);

    Direction newDirection = getPointsDirection(currentPos, targetPos);

    if (newDirection != this->direction) {
        this->pointIndex++;
        if(this->pointIndex>=this->map->getRoadPoints().size()){
            return 0;
        }
        this->direction = getPointsDirection(this->map->roadPoint(this->pointIndex-1), this->map->roadPoint(this->pointIndex));
    }


    QPoint otherPos = this->pos().toPoint();

    switch (this->direction) {
    case Direction::North:
        currentPos.setY(std::max(currentPos.y() - this->speed,this->map->roadPoint(this->pointIndex).y()));
        break;
    case Direction::South:
        currentPos.setY(std::min(currentPos.y() + this->speed,this->map->roadPoint(this->pointIndex).y()));
        break;
    case Direction::East:
        currentPos.setX(std::min(currentPos.x() + this->speed,this->map->roadPoint(this->pointIndex).x()));
        break;
    case Direction::West:
        currentPos.setX(std::max(currentPos.x() - this->speed,this->map->roadPoint(this->pointIndex).x()));
        break;
    default:
        break;
    }

    this->setPos(currentPos);

    return std::max(std::abs(otherPos.x()-currentPos.x()),std::abs(otherPos.y()-currentPos.y()));
}



std::pair<int,int> Enemy::getCenter(){
    return std::make_pair(pos().x()+this->map->getSquareSize()/2,pos().y() + this->map->getSquareSize()/2);
}

int Enemy::getRadius(){
    return this->map->getSquareSize()/4;
}





Enemy::~Enemy(){
    this->level=0;
    this->health=0;
    this->speed=0;
    this->pointIndex=0;
    this->map=nullptr;
}






































