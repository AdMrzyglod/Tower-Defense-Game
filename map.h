#ifndef MAP_H
#define MAP_H







#include "bullet.h"
#include "gameconfig.h"

#include <iostream>
#include <vector>
#include <utility>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QPoint>
#include <QVector>
#include <./ui_mainwindow.h>

class Enemy;

class TowerPlace;

class Tower;

class Game;

class Map
{
public:
    Map(Game* game);
    ~Map();
    void drawMap();
    QGraphicsScene* getScene();
    int getRows();
    int getCols();
    int getSquareSize();
    std::vector<std::pair<int,int>> getRoadPoints();
    QPoint roadPoint(int index);
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    void moveEnemies();
    void updateWaves();
    void addEnemyToDelete(Enemy* enemy);
    void deleteEnemies();
    void towersAction();
    void moveBullets();

    void addBullet(Bullet* bullet);
    void removeBullet(Bullet* bullet);
    void addBulletToDelete(Bullet* bullet);
    void deleteBullets();

    std::vector<Enemy*>* getEnemies();

    Game* getGame();

private:
    QGraphicsScene* scene;
    Game* game;
    int rows;
    int cols;
    int squareSize;
    std::vector<std::pair<int,int>> roadPoints;
    std::vector<Enemy*> enemyVector;
    std::vector<Enemy*> enemyToDelete;
    std::vector<std::pair<int,int>> towerPoints;
    std::vector<TowerPlace*> towerPlaces;
    std::vector<Wave> waves;
    int wavesIndex;
    std::vector<Bullet*> bullets;
    std::vector<Bullet*> bulletsToDelete;
    int counter;

    void initRoad();
    void initTowerPlaces();
    void initWaves();
    void drawRoad();
    void drawTowerPlaces();
    bool inMap(std::pair<int,int> point);
};

#endif // MAP_H
