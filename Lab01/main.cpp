#include <QApplication>
#include "mainwindow.h"
#include "routesmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RoutesManager man;
    MainWindow w;
    w.setRoutesManager(&man);
    w.show();


    return a.exec();
}
