#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"
#include "ui_mainwindow.h"
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->filename=":/config/config.json";
    ui->setupUi(this);
    stopClicked=false;
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStopButton);
    connect(ui->resetButton, &QAction::triggered, this, &MainWindow::onResetButton);
    connect(ui->startButton,&QPushButton::clicked, this, &MainWindow::onStartButton);
    connect(ui->menuButton, &QAction::triggered, this, &MainWindow::onMenuButton);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->centralwidget->resize(1500,900);
    ui->graphicsView->setFixedSize(1450,900);
    ui->graphicsView->setSceneRect(-20, -40,1480,860);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->move(20,20);
    ui->graphicsView->setBackgroundBrush(QColor("green"));
    ui->centralwidget->setStyleSheet("background-color: green;");
    ui->startButton->setStyleSheet("font-size: 20px;");
    ui->stopButton->setDisabled(true);
    ui->stopButton->setHidden(true);
    ui->healthLabel->setHidden(true);
    ui->destroyLabel->setHidden(true);
    ui->moneyLabel->setHidden(true);
    ui->healthLabel->setStyleSheet("font-size: 20px;");
    ui->destroyLabel->setStyleSheet("font-size: 20px;");
    ui->moneyLabel->setStyleSheet("font-size: 20px;");
    ui->defeatLabel->setHidden(true);
    ui->victoryLabel->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete game;
    delete ui;
    this->filename.clear();
}


void MainWindow::onStopButton(bool checked){

    if(!stopClicked){
        ui->stopButton->setText("Wznów");
        game->stopTimer();
    }
    else{
        ui->stopButton->setText("Zatrzymaj");
        game->startTimer();
    }
    stopClicked=!stopClicked;
}

void MainWindow::onResetButton(bool checked){
    ui->defeatLabel->setHidden(true);
    ui->victoryLabel->setHidden(true);
    if(this->game!=nullptr){
        ui->graphicsView->setScene(nullptr);
        delete this->game;
    }

    this->game = new Game(this->filename,this);
    ui->graphicsView->setScene(this->game->getGameMap()->getScene());
    stopClicked=false;
    ui->stopButton->setText("Zatrzymaj");
    game->startTimer();
}


void MainWindow::onStartButton(bool checked){
    ui->startButton->setDisabled(true);
    ui->startButton->setHidden(true);
    ui->label->setHidden(true);
    ui->stopButton->setDisabled(false);
    ui->stopButton->setHidden(false);
    ui->healthLabel->setHidden(false);
    ui->destroyLabel->setHidden(false);
    ui->moneyLabel->setHidden(false);
    this->game = new Game(this->filename,this);
    ui->graphicsView->setScene(this->game->getGameMap()->getScene());
    game->startTimer();
}

void MainWindow::onMenuButton(bool checked){
    ui->defeatLabel->setHidden(true);
    ui->victoryLabel->setHidden(true);
    ui->stopButton->setDisabled(true);
    ui->stopButton->setHidden(true);
    ui->healthLabel->setHidden(true);
    ui->destroyLabel->setHidden(true);
    ui->moneyLabel->setHidden(true);
    ui->startButton->setDisabled(false);
    ui->startButton->setHidden(false);
    ui->label->setHidden(false);
    if(this->game!=nullptr){
        delete this->game;
    }
    this->game=nullptr;
    ui->graphicsView->setScene(nullptr);
}


void MainWindow::updateLabels(int money,int enemies,int health){
    ui->healthLabel->setText(QString("Health: ") + QString::number(health));
    ui->moneyLabel->setText(QString("Money: ") + QString::number(money));
    ui->destroyLabel->setText(QString("Destroyed enemies: ") + QString::number(enemies));
}



void MainWindow::defeatLabel(){
    ui->defeatLabel->setHidden(false);
}


void MainWindow::victoryLabel(){
    ui->victoryLabel->setHidden(false);
}













