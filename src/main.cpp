#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;

    window.resize(1500,900);

    window.show();

    return a.exec();
}
