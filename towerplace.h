#ifndef TOWERPLACE_H
#define TOWERPLACE_H


#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "map.h"

class TowerPlace : public QGraphicsPixmapItem, public QObject
{
public:
    TowerPlace(QGraphicsItem* parent = nullptr,Map* map = nullptr,std::pair<int,int> point = std::make_pair(0,0));

    ~TowerPlace();

    void setTower(Tower* tower);

    void removeTower();

    bool isActive();

    Tower* getTower();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    QPushButton* sellButton;
    QPushButton* upgradeButton;

public slots:
    void onSellButton();
    void onUpgradeButton();

private:
    Map* map;
    std::pair<int,int> point;
    bool showInterface;
    int towerLevel;
    bool active;
    Tower* tower;
};

#endif
