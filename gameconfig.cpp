#include "gameconfig.h"


GameConfig::GameConfig(int refreshTime,int gameHealth,int money,int rows,int cols,
                       int squareSize,std::vector<std::pair<int,int>> roadPoints,std::vector<std::pair<int,int>> towerPoints
                       ,std::vector<Wave> waves,std::vector<EnemyDetails> enemyDetails,std::vector<TowerDetails> towerDetails){
    this->refreshTime = refreshTime;
    this->gameHealth= gameHealth;
    this->gameMoney=money;
    this->map.rows=rows;
    this->map.cols = cols;
    this->map.squareSize=squareSize;
    this->map.roadPoints=roadPoints;
    this->map.towerPoints=towerPoints;
    this->waves=waves;
    this->enemyDetails=enemyDetails;
    this->towerDetails=towerDetails;
}



GameConfig::~GameConfig(){

    this->gameHealth=0;
    this->gameMoney=0;
    this->refreshTime=0;
    this->map.roadPoints.clear();
    this->map.towerPoints.clear();
    this->enemyDetails.clear();
    this->towerDetails.clear();
    this->waves.clear();
}
