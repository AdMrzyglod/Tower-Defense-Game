#include "map.h"
#include "enemy.h"
#include "game.h"
#include "tower.h"
#include "towerplace.h"

#include <QGraphicsProxyWidget>
#include <QVBoxLayout>

Map::Map(Game* game)
{
    this->counter = 0;
    this->scene = new QGraphicsScene();
    this->rows=game->getConfig()->getRows();
    this->cols=game->getConfig()->getCols();
    this->squareSize=game->getConfig()->getSquareSize();
    this->game = game;

    initRoad();

    initWaves();

    initTowerPlaces();

    drawMap();
}


void Map::initRoad(){

    this->roadPoints.insert(this->roadPoints.end(),this->getGame()->getConfig()->getRoadPoints()->begin(),this->getGame()->getConfig()->getRoadPoints()->end());
}



void Map::initTowerPlaces(){

    this->towerPoints.insert(this->towerPoints.end(),this->getGame()->getConfig()->getTowerPoints()->begin(),this->getGame()->getConfig()->getTowerPoints()->end());
}

void Map::initWaves(){
    this->wavesIndex=0;
    this->waves.insert(this->waves.end(),this->getGame()->getConfig()->getWaves()->begin(),this->getGame()->getConfig()->getWaves()->end());

    for(int i=0;i<this->waves.size();i++){
        this->waves[i].firstDelay=std::round(this->waves[i].firstDelay*1000/this->getGame()->getConfig()->getRefreshTime());
        this->waves[i].delay=std::round(this->waves[i].delay*1000/this->getGame()->getConfig()->getRefreshTime());
    }
}

void Map::updateWaves(){

    if(this->wavesIndex==this->waves.size()){
        if(this->enemyVector.size()==0){
            this->getGame()->stopTimer();
            this->getGame()->getMainWindow()->victoryLabel();
        }
        return;
    }

    if(this->waves[this->wavesIndex].firstDelay==0){

        counter--;
        if(counter==0){

             this->waves[this->wavesIndex].numberOfEnemies--;
             this->addEnemy(new Enemy(this->waves[this->wavesIndex].enemiesLevel,this));
             this->counter= std::round(this->waves[this->wavesIndex].delay);

             if(this->waves[this->wavesIndex].numberOfEnemies==0){
                  this->wavesIndex++;
             }
        }
    }
    else{
        this->waves[this->wavesIndex].firstDelay--;
        if(this->waves[this->wavesIndex].firstDelay==0){
             counter = std::round(this->waves[this->wavesIndex].delay);
        }
    }
}

void Map::drawMap(){

    this->scene->setSceneRect(0,0,1600,900);


    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {

            QGraphicsRectItem *rect = new QGraphicsRectItem(i * getSquareSize(), j * getSquareSize(), getSquareSize(), getSquareSize());

            rect->setBrush(QPixmap(":/images/grass.png").scaled(getSquareSize(),getSquareSize()));

            this->scene->addItem(rect);

        }
    }

    drawRoad();

    drawTowerPlaces();

}

void Map::drawRoad(){
    for(int i=0; i<this->roadPoints.size()-1;i++){
        int start,end;

        if(this->roadPoints.at(i).first-this->roadPoints.at(i+1).first==0){
            int r=this->roadPoints.at(i).first;
            start=std::min(this->roadPoints.at(i).second,this->roadPoints.at(i+1).second);
            end=std::max(this->roadPoints.at(i).second,this->roadPoints.at(i+1).second);


            for(int c=start;c<=end;c++){

                QGraphicsItem* item = this->scene->itemAt(r * getSquareSize(), c * getSquareSize(),QTransform());

                if (dynamic_cast<QGraphicsRectItem*>(item)){
                    QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(item);
                    rectItem->setBrush(QBrush(QPixmap(":/images/road.png").scaled(getSquareSize(),getSquareSize())));
                }
            }
        }
        else{

            int c=this->roadPoints.at(i).second;
            start=std::min(this->roadPoints.at(i).first,this->roadPoints.at(i+1).first);
            end=std::max(this->roadPoints.at(i).first,this->roadPoints.at(i+1).first);

            for(int r=start;r<=end;r++){

                QGraphicsItem* item = this->scene->itemAt(r * getSquareSize(), c * getSquareSize(),QTransform());

                if (dynamic_cast<QGraphicsRectItem*>(item)){
                    QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(item);
                    rectItem->setBrush(QBrush(QPixmap(":/images/road.png").scaled(getSquareSize(),getSquareSize())));
                }
            }
        }
    }
}


void Map::drawTowerPlaces(){

    for(int i=0;i<this->towerPoints.size();i++){

        TowerPlace* tower = new TowerPlace(nullptr,this,towerPoints[i]);

        this->towerPlaces.push_back(tower);

        this->scene->addItem(tower);
    }
}



QGraphicsScene* Map::getScene(){
    return this->scene;
}


int Map::getRows(){
    return rows;
}


int Map::getCols(){
    return cols;
}


int Map::getSquareSize(){
    return squareSize;
}


std::vector<std::pair<int,int>> Map::getRoadPoints(){
    return this->roadPoints;
}

QPoint Map::roadPoint(int index){
    int midX= this->getRoadPoints().at(index).first*this->getSquareSize();
    int midY= this->getRoadPoints().at(index).second*this->getSquareSize();
    return QPoint(midX,midY);
}


void Map::addEnemy(Enemy* enemy){
    this->enemyVector.push_back(enemy);
    this->scene->addItem(enemy);
}


void Map::removeEnemy(Enemy* enemy){
    auto it = std::remove(this->enemyVector.begin(),this->enemyVector.end(),enemy);
    this->enemyVector.erase(it,this->enemyVector.end());
    this->scene->removeItem(enemy);
    delete enemy;
}


void Map::moveEnemies(){

    for(int i=0;i<enemyVector.size();i++){
        enemyVector[i]->move();
    }

    deleteEnemies();
}


Game* Map::getGame(){
    return this->game;
}

void Map::deleteEnemies(){

    for(int i=0;i<this->enemyToDelete.size();i++){
        removeEnemy(this->enemyToDelete[i]);
    }
    this->enemyToDelete.clear();
}

void Map::addEnemyToDelete(Enemy* enemy){
    this->enemyToDelete.push_back(enemy);
}


std::vector<Enemy*>* Map::getEnemies(){
    return &this->enemyVector;
}


void Map::towersAction(){

    for(int i=0;i<this->towerPlaces.size();i++){

        if(this->towerPlaces[i]->isActive()){
            this->towerPlaces[i]->getTower()->shot();
        }
    }
}




void Map::addBullet(Bullet* bullet){
    this->bullets.push_back(bullet);
    this->scene->addItem(bullet);
}


void Map::removeBullet(Bullet* bullet){
    auto it = std::remove(this->bullets.begin(),this->bullets.end(),bullet);
    this->bullets.erase(it,this->bullets.end());
    this->scene->removeItem(bullet);
    delete bullet;
}

void Map::addBulletToDelete(Bullet* bullet){
    this->bulletsToDelete.push_back(bullet);
}

void Map::deleteBullets(){

    for(int i=0;i<this->bulletsToDelete.size();i++){
        removeBullet(this->bulletsToDelete[i]);
    }
    this->bulletsToDelete.clear();
}


bool Map::inMap(std::pair<int,int> point){

    if(point.first<= this->rows*getSquareSize() && point.first>=0 && point.second<= this->cols*getSquareSize() && point.second>=0){
        return true;
    }

    return false;
}

void Map::moveBullets(){

    for(int i=0;i<bullets.size();i++){
        bullets[i]->move();

        if(!inMap(bullets[i]->getPosition())){
            addBulletToDelete(bullets[i]);
            continue;
        }

        for(int j=0;j<enemyVector.size();j++){
            if(bullets[i]->isHit(enemyVector[j]) && enemyVector[j]->healthAboveZero()){

                addBulletToDelete(bullets[i]);
                enemyVector[j]->updateHealth(-bullets[i]->getDamage());

                if(!enemyVector[j]->healthAboveZero()){
                    addEnemyToDelete(enemyVector[j]);
                    this->getGame()->updateMoney(this->getGame()->getConfig()->getEnemyDetails()->at(this->enemyVector[j]->getLevel()).moneyFromEnemy);
                    this->getGame()->updateDestroyedEnemies();
                }

                break;

            }
        }
    }

    deleteBullets();
    deleteEnemies();
}




Map::~Map(){
    this->game=nullptr;
    this->rows=0;
    this->cols=0;
    this->squareSize=0;
    this->roadPoints.clear();

    for(auto enemy: this->enemyVector){
        this->scene->removeItem(enemy);
        delete enemy;
    }
    this->enemyVector.clear();
    this->enemyToDelete.clear();
    this->towerPoints.clear();
    for(auto towerPlace: this->towerPlaces){
        this->scene->removeItem(towerPlace);
        delete towerPlace;
    }
    this->towerPlaces.clear();
    this->waves.clear();
    this->wavesIndex=0;

    for(auto bullet: this->bullets){
        this->scene->removeItem(bullet);
        delete bullet;
    }
    this->bullets.clear();
    this->bulletsToDelete.clear();
    this->counter=0;

    for(auto item: this->scene->items()){
        this->scene->removeItem(item);
        delete item;
    }
    this->scene->clear();
    delete this->scene;
}



























