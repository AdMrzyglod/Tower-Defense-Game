#include "towerplace.h"
#include "game.h"
#include "tower.h"



TowerPlace::TowerPlace(QGraphicsItem *parent, Map *map, std::pair<int, int> point)
    : QGraphicsPixmapItem(parent)
{
    this->tower=nullptr;
    this->map = map;
    this->showInterface=false;
    this->active=false;
    this->towerLevel=0;
    this->point=point;
    setPixmap(QPixmap(":/images/towerPlus.png").scaled(map->getSquareSize(), map->getSquareSize()));

    this->setZValue(0);

    sellButton = new QPushButton("$");
    upgradeButton = new QPushButton("^");

    QObject::connect(sellButton,&QPushButton::clicked, this, &TowerPlace::onSellButton);
    QObject::connect(upgradeButton,&QPushButton::clicked, this, &TowerPlace::onUpgradeButton);

    QString buttonStyle = "QPushButton {"
                          "background-color: gold;"
                          "border: 2px solid #333333;"
                          "border-radius: 5px;"
                          "padding: 4px;"
                          "margin: 14px;"
                          "}";

    sellButton->setStyleSheet(buttonStyle);
    upgradeButton->setStyleSheet(buttonStyle);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(sellButton);
    layout->addWidget(upgradeButton);

    QWidget* widget = new QWidget;
    widget->setLayout(layout);

    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget(this);
    proxyWidget->setWidget(widget);
    proxyWidget->setPos(-40, 0);

    widget->setStyleSheet("background-color: transparent;");

    int widgetWidth = map->getSquareSize()+80;
    int widgetHeight = map->getSquareSize();
    widget->setFixedSize(widgetWidth, widgetHeight);


    this->setPos(point.first * map->getSquareSize(), point.second * map->getSquareSize());

    proxyWidget->hide();
}



void TowerPlace::onSellButton(){
    if(this->towerLevel>0){
         this->active=false;
         this->map->getGame()->updateMoney(this->map->getGame()->getConfig()->getTowerDetails()->at(this->towerLevel-1).price/2);
         this->towerLevel=0;
         removeTower();
         setPixmap(QPixmap(":/images/towerPlus.png").scaled(map->getSquareSize(), map->getSquareSize()));
    }
}

void TowerPlace::onUpgradeButton(){

    if(this->towerLevel<this->map->getGame()->getConfig()->getTowerDetails()->size() && this->map->getGame()->getMoney()-this->map->getGame()-> getConfig()->getTowerDetails()->at(this->towerLevel).price>=0){
        this->active=true;
        setPixmap(QPixmap(":/images/grass.png").scaled(map->getSquareSize(), map->getSquareSize()));
        this->towerLevel++;
        this->map->getGame()->updateMoney(-this->map->getGame()->getConfig()->getTowerDetails()->at(this->towerLevel-1).price);
        if(this->towerLevel>1){
            removeTower();
        }
        Tower* tower = new Tower(this->map,point,this,this->towerLevel);
        setTower(tower);
    }
}


void TowerPlace::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
        if (!this->showInterface)
        {
            QGraphicsPixmapItem::mousePressEvent(event);
            QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(childItems().first());
            proxyWidget->show();
        }
        else
        {
            QGraphicsPixmapItem::mousePressEvent(event);
            QGraphicsProxyWidget* proxyWidget = dynamic_cast<QGraphicsProxyWidget*>(childItems().first());
            proxyWidget->hide();
        }
        this->showInterface=!this->showInterface;
}


void TowerPlace::setTower(Tower* tower){
        this->map->getScene()->addItem(tower);
        this->tower=tower;
}

void TowerPlace::removeTower(){
        this->map->getScene()->removeItem(tower);
        delete this->tower;
        this->tower=nullptr;
}



Tower* TowerPlace::getTower(){
        return this->tower;
}


bool TowerPlace::isActive(){
        return this->active;
}




TowerPlace::~TowerPlace(){
        this->map=nullptr;
        if(this->tower!=nullptr){
            delete this->tower;
        }
        this->towerLevel=0;
}
























