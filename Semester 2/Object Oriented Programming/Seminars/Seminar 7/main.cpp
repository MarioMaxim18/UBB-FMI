#include "mainwindow.h"
#include "Repository.h"
#include "Controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository songRepo{};
    Controller songController{songRepo};

    MainWindow w{songController};
    w.show();

    return a.exec();
}
