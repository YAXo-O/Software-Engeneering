#include <QApplication>
#include "mainwindow.h"
#include "routesmanager.h"
#include "Parsers/gpxparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RoutesManager man;
    MainWindow w;
    GPXParser parser;
    parser.parse("./berlin_moscow.gpx", &man);

    w.show();
    w.setRoutesManager(&man);


    return a.exec();
}
