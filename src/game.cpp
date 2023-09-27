#include "dataparser.h"
#include "game.h"



Game::Game(std::string filename,MainWindow* mainWindow)
{
    this->window=mainWindow;
    this->config = DataParser::parseJSON(filename);
    this->gameMap= new Map(this);
    this->money=config->getGameMoney();
    this->destroyedEnemies=0;
    this->health=config->getGameHealth();
    this->window->updateLabels(this->money,this->destroyedEnemies,this->health);
    initTimer();
}


Game::~Game()
{
    stopTimer();
    this->window=nullptr;
    delete timer;
    delete config;
    delete gameMap;
    this->money=0;
    this->destroyedEnemies=0;
    this->health=0;
}



void Game::initTimer(){
    this->timer= new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    this->timer->setInterval(-1);
}


void Game::startTimer(){
    this->timer->start(this->config->getRefreshTime());
}


void Game::stopTimer(){
    this->timer->stop();
}

void Game::run(){
    this->gameMap->moveEnemies();

    this->gameMap->moveBullets();

    this->gameMap->towersAction();

    this->gameMap->updateWaves();

    this->window->updateLabels(this->money,this->destroyedEnemies,this->health);

    if(this->health<=0){
        stopTimer();
        this->window->defeatLabel();
    }
}


void Game::updateMoney(int money){
    this->money+=money;
}


void Game::updateDestroyedEnemies(){
    this->destroyedEnemies++;
}


void Game::updateHealth(int damage){
    this->health+=damage;
}

GameConfig* Game::getConfig(){
    return this->config;
}










