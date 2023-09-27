#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#include <vector>
#include <string>
#include <QString>


typedef struct MapConfig{
    int rows;
    int cols;
    int squareSize;
    std::vector<std::pair<int,int>> roadPoints;
    std::vector<std::pair<int,int>> towerPoints;
} MapConfig;


typedef struct Wave{
    double firstDelay;
    int numberOfEnemies;
    double delay;
    int enemiesLevel;
} Wave;


typedef struct EnemyDetails{
    int health;
    int speed;
    int moneyFromEnemy;
    int damageFromEnemy;
    QString image;
} EnemyDetails;


typedef struct TowerDetails{
    int radius;
    double rateOfFire;
    int price;
    QString image;
    int bulletSpeed;
    int bulletDamage;
    QString bulletImage;
} TowerDetails;


class GameConfig{

public:
    GameConfig(int refreshTime,int gameHealth,int money,int rows,int cols, int squareSize,
               std::vector<std::pair<int,int>> roadPoints,std::vector<std::pair<int,int>> towerPoints,
               std::vector<Wave> waves,std::vector<EnemyDetails> enemyDetails,std::vector<TowerDetails> towerDetails);

    ~GameConfig();
    int getRefreshTime(){
        return refreshTime;
    }

    int getGameHealth(){
        return gameHealth;
    }
    int getGameMoney(){
        return gameMoney;
    }
    int getRows(){
        return map.rows;
    }
    int getCols(){
        return map.cols;
    }
    int getSquareSize(){
        return map.squareSize;
    }
    std::vector<std::pair<int,int>>* getRoadPoints(){
        return &map.roadPoints;
    }
    std::vector<std::pair<int,int>>* getTowerPoints(){
        return &map.towerPoints;
    }
    std::vector<Wave>* getWaves(){
        return &waves;
    }
    std::vector<EnemyDetails>* getEnemyDetails(){
        return &enemyDetails;
    }
    std::vector<TowerDetails>* getTowerDetails(){
        return &towerDetails;
    }


private:
    int refreshTime;
    int gameHealth;
    int gameMoney;
    MapConfig map;
    std::vector<Wave> waves;
    std::vector<EnemyDetails> enemyDetails;
    std::vector<TowerDetails> towerDetails;
};



#endif // GAMECONFIG_H
