#include "guitest.h"
#include "testpresenter.h"
#include "../mainwindow.h"

void runTests()
{
    TestPresenter p;
    MainWindow w;

    QObject::connect(&w, SIGNAL(createRoute()), &p, SLOT(createRoute()));
    QObject::connect(&w, SIGNAL(createPoint()), &p, SLOT(createPoint()));
    QObject::connect(&w, SIGNAL(removePoint(QItemSelectionModel*)), &p, SLOT(removePoint(QItemSelectionModel*)));
    QObject::connect(&w, SIGNAL(drawHeightMap(QItemSelectionModel*)), &p, SLOT(drawHeightMap(QItemSelectionModel*)));

    w.runGUITests();
}

