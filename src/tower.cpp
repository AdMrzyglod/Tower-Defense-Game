#include "tower.h"
#include "towerplace.h"
#include "game.h"

Tower::Tower(Map* map,std::pair<int,int> position,TowerPlace* towerPlace,int level)
{
    this->map=map;
    this->level=level;
    setPixmap(QPixmap(":/images/"+this->map->getGame()->getConfig()->getTowerDetails()->at(level-1).image).scaled(map->getSquareSize(),map->getSquareSize()*6/4));
    this->towerPlace = towerPlace;
    this->pixelRadius=this->map->getGame()->getConfig()->getTowerDetails()->at(level-1).radius;
    this->rateOfFire=std::round(this->map->getGame()->getConfig()->getTowerDetails()->at(level-1).rateOfFire*1000/this->map->getGame()->getConfig()->getRefreshTime());
    this->counter=0;
    this->afterShot=false;
    this->center = std::make_pair(position.first*map->getSquareSize()+map->getSquareSize()/2,position.second*map->getSquareSize()+map->getSquareSize()/2);
    setZValue(2);
    setPos(position.first*map->getSquareSize(),position.second*map->getSquareSize()-map->getSquareSize()*2/4);
}




void Tower::shot(){

    if(!this->afterShot){

        for(int i=0;i<this->map->getEnemies()->size();i++){

            if(enemyInRange(this->map->getEnemies()->at(i))){

                Enemy* enemy = this->map->getEnemies()->at(i);

                Enemy testEnemy(*enemy);

                bool sendShot=false;

                int distance=0;

                while(true){

                    int value=testEnemy.testMove();

                    if(!enemyInRange(&testEnemy) || value==0){
                        break;
                    }

                    distance+=value;

                     if(pointInRange(testEnemy.getCenter())){
                         int time = distance/enemy->getSpeed();
                         int dt=enemy->getRadius()/enemy->getSpeed();
                         int bulletTime=getDistance(this->center,testEnemy.getCenter())/this->map->getGame()-> getConfig()->getTowerDetails()->at(level-1).bulletSpeed;

                         if(time-dt<=bulletTime && time+dt>=bulletTime){
                             sendBulletToPoint(testEnemy.getCenter());
                             sendShot=true;
                             break;
                         }
                     }
                }

                if(sendShot){
                     this->afterShot=true;

                     break;
                }
            }
        }
    }
    else{
        this->counter++;

        if(this->counter==this->rateOfFire){
            this->counter=0;
            this->afterShot=false;
        }

    }

}






bool Tower::enemyInRange(Enemy* enemy){

    std::pair<int,int> towerCenter = this->center;
    int towerRadius = this->pixelRadius;

    std::pair<int,int> enemyCenter = enemy->getCenter();
    int enemyRadius = enemy->getRadius();

    int distance = sqrt(pow(towerCenter.first - enemyCenter.first, 2) + pow(towerCenter.second - enemyCenter.second, 2))-enemyRadius;

    if(towerRadius>=distance){
        return true;
    }
    else{
        return false;
    }
}



bool Tower::pointInRange(std::pair<int,int> point){

    std::pair<int,int> towerCenter = this->center;
    int towerRadius = this->pixelRadius;

    int distance = sqrt(pow(towerCenter.first - point.first, 2) + pow(towerCenter.second - point.second, 2));

    if(towerRadius>=distance){
        return true;
    }
    else{
        return false;
    }
}



void Tower::sendBulletToPoint(std::pair<int,int> point){
    new Bullet(this->center,point,this->level,this->map);
}



double Tower::getDistance(std::pair<int,int> point1,std::pair<int,int> point2){
    return sqrt(pow(point1.first - point2.first, 2) + pow(point1.second - point2.second, 2));
}




Tower::~Tower(){
    this->map=nullptr;
    this->pixelRadius=0;
    this->rateOfFire=0;
    this->level=0;
    this->counter=0;
    this->afterShot=0;
    this->towerPlace=nullptr;
}























