#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateLabels(int money,int enemies,int health);
    void defeatLabel();
    void victoryLabel();

public:
    Ui::MainWindow *ui;
    Game* game;
    bool stopClicked;
    std::string filename;
public slots:
    void onStopButton(bool checked);
    void onResetButton(bool checked);
    void onStartButton(bool checked);
    void onMenuButton(bool checked);
};
#endif // MAINWINDOW_H
