#ifndef GAME_H
#define GAME_H

#include "gameconfig.h"
#include "mainwindow.h"
#include "map.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>


class Game: public QObject
{
    Q_OBJECT
public:
    Game(std::string filename,MainWindow* mainWindow);
    ~Game();

    Map* getGameMap(){
        return this->gameMap;
    }

    void initTimer();
    void startTimer();
    void stopTimer();

    void updateMoney(int money);
    void updateDestroyedEnemies();
    void updateHealth(int damage);
    GameConfig* getConfig();

    int getMoney(){
        return money;
    }
    int getGameHealth(){
        return health;
    }
    MainWindow* getMainWindow(){
        return window;
    }

public slots:
    void run();

private:
    MainWindow* window;
    GameConfig* config;
    Map* gameMap;
    QTimer* timer;
    int money;
    int destroyedEnemies;
    int health;

};

#endif // GAME_H
