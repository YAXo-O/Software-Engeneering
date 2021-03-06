#include <QApplication>
#include "mainwindow.h"

#include "presenter.h"
#include "model.h"
#include "Tests/guitest.h"

#define GUITESTS_NO

void connectToView(Presenter &presenter, const MainWindow &window);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef GUITESTS
    runTests();
#endif

    MainWindow w;
    Presenter presenter;
    Model model;

    model.init();
    presenter.setModel(&model);
    presenter.setRoutesView(w.getRoutesView());
    presenter.setPointsView(w.getPointsView());
    presenter.setConnections();
    w.setConnections();
    connectToView(presenter, w);
    QObject::connect(&presenter, SIGNAL(sendVisitor(AbstractVisitor*)), &model, SLOT(receiveVisitor(AbstractVisitor*)));

    w.show();

    return a.exec();
}

void connectToView(Presenter &presenter, const MainWindow &window)
{
    QObject::connect(&window, SIGNAL(createRoute()), &presenter, SLOT(createRoute()));
    QObject::connect(&window, SIGNAL(removeRoute(QItemSelectionModel*)), &presenter, SLOT(removeRoute(QItemSelectionModel*)));
    QObject::connect(&window, SIGNAL(createPoint()), &presenter, SLOT(createPoint()));
    QObject::connect(&window, SIGNAL(removePoint(QItemSelectionModel*)), &presenter, SLOT(removePoint(QItemSelectionModel*)));
    QObject::connect(&window, SIGNAL(doReset()), &presenter, SLOT(reset()));
    QObject::connect(&window, SIGNAL(loadFile(QString)), &presenter, SLOT(loadFile(QString)));
    QObject::connect(&window, SIGNAL(changeLongitude(QItemSelectionModel*,double)),
                     &presenter, SLOT(changeLongitude(QItemSelectionModel*,double)));
    QObject::connect(&window, SIGNAL(changeLatitude(QItemSelectionModel*,double)),
                     &presenter, SLOT(changeLatitude(QItemSelectionModel*,double)));
    QObject::connect(&window, SIGNAL(changeHeight(QItemSelectionModel*,double)),
                     &presenter, SLOT(changeHeight(QItemSelectionModel*,double)));
    QObject::connect(&window, SIGNAL(undo()), &presenter, SLOT(undo()));
    QObject::connect(&window, SIGNAL(redo()), &presenter, SLOT(redo()));
    QObject::connect(&window, SIGNAL(routeTableSelectionChanged(QModelIndex)), &presenter, SLOT(routeTableSelectionChanged(QModelIndex)));
    QObject::connect(&window, SIGNAL(pointsTableSelectionChanged(QModelIndex)), &presenter, SLOT(pointsTableSelectionChanged(QModelIndex)));
    QObject::connect(&presenter, SIGNAL(currentName(QString)), &window, SLOT(currentRoute(QString)));
    QObject::connect(&presenter, SIGNAL(currentPoint(double,double, double)), &window, SLOT(currentPoint(double,double, double)));
    QObject::connect(&window, SIGNAL(renameRoute(QItemSelectionModel*,QString)), &presenter, SLOT(renameRoute(QItemSelectionModel*,QString)));
    QObject::connect(&window, SIGNAL(readPolyline(QString)), &presenter, SLOT(readPolyline(QString)));
    QObject::connect(&window, SIGNAL(writePolyline(QString)), &presenter, SLOT(writePolyline(QString)));
    QObject::connect(&presenter, SIGNAL(sendError(QString,QString,errorLevel)), &window, SLOT(receiveError(QString,QString,errorLevel)));
    QObject::connect(&window, SIGNAL(drawHeightMap(QItemSelectionModel*)), &presenter, SLOT(drawHeightMap(QItemSelectionModel*)));
    QObject::connect(&presenter, SIGNAL(addPointToGraph(double,double)), &window, SLOT(addPointToGraph(double,double)));
    QObject::connect(&presenter, SIGNAL(displayGraph()), &window, SLOT(displayGraph()));
    QObject::connect(&presenter, SIGNAL(clearGraph()), &window, SLOT(clearGraph()));
    QObject::connect(&window, SIGNAL(getPluginManager()), &presenter, SLOT(getPluginTable()));
    QObject::connect(&presenter, SIGNAL(sendPluginTable(QHash<QString,loaderData>*)), &window,
                     SLOT(pluginManager(QHash<QString,loaderData>*)));
    QObject::connect(&window, SIGNAL(sendVisitor(AbstractVisitor*)), &presenter, SIGNAL(sendVisitor(AbstractVisitor*)));
}

