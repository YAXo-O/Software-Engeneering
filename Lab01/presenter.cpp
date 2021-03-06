#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>

#include "presenter.h"

#include "../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.h"
#include "model.h"
#include "pointssaver.h"
#include "pluginmanager.h"

Presenter::Presenter(QObject *parent) : QObject(parent), model(nullptr), routesView(nullptr), pointsView(nullptr),
    pManager(nullptr), pThread(nullptr)
{
}

Model *Presenter::getModel() const
{
    return model;
}

void Presenter::setModel(Model *value)
{
    model = value;

    createPluginManager();
}

QTableView *Presenter::getRoutesView() const
{
    return routesView;
}

void Presenter::setRoutesView(QTableView *value)
{
    routesView = value;
}

QTableView *Presenter::getPointsView() const
{
    return pointsView;
}

void Presenter::setPointsView(QTableView *value)
{
    pointsView = value;
}

void Presenter::setConnections()
{
    routesView->setModel(model->getRoutes());
    pointsView->setModel(model->getPoints());
    connect(model, &Model::needsUpdate, [this]()
    {
        model->getRoutes()->setQuery(model->getDbManager()->routeQuery());
        model->getPoints()->setQuery(model->getDbManager()->pointsQuery());
    });
    connect(model->getDbManager(), SIGNAL(selectionChanged(int,int)), SLOT(currentRouteChanged(int, int)));
}

void Presenter::loadFile(const QString &filename)
{
    if(filename == "")
        return;

    try
    {
        cManager.receive(factory.importFile(filename, *model->getDbManager()));
    }
    catch(std::ios_base::failure &failure)
    {
        emit sendError("File failure!", "Can't open specified file!", EL_WARNING);
    }
    catch(std::invalid_argument &failure)
    {
        emit sendError("File failure!", "Can't parse .gpx file!\n" + QString(failure.what()), EL_WARNING);
    }
}

void Presenter::undo()
{
    cManager.undo();
}

void Presenter::redo()
{
    cManager.redo();
}

void Presenter::reset()
{
    cManager.receive(factory.reset(*model->getDbManager()));
}

void Presenter::renameRoute(QItemSelectionModel *selection, const QString &newName)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.first().row();
        QModelIndex index = model->getRoutes()->index(row, 0);
        int id = model->getRoutes()->data(index).toInt();
        index = model->getRoutes()->index(row, 1);
        QString oldName = model->getRoutes()->data(index).toString();

        cManager.receive(factory.renameRoute(oldName, newName, *model->getDbManager(), id));
    }

}

void Presenter::changeLongitude(QItemSelectionModel *selection, double newLongitude)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.first().row();
        QModelIndex index = model->getPoints()->index(row, 0);
        int id = model->getPoints()->data(index).toInt();
        index = model->getPoints()->index(row, 1);
        double oldLongitude = model->getPoints()->data(index).toDouble();

        cManager.receive(factory.changeLongitude(*model->getDbManager(), oldLongitude, newLongitude, id));
    }
}

void Presenter::changeLatitude(QItemSelectionModel *selection, double newLatitude)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.first().row();
        QModelIndex index = model->getPoints()->index(row, 0);
        int id = model->getPoints()->data(index).toInt();
        index = model->getPoints()->index(row, 2);
        double oldLatitude = model->getPoints()->data(index).toDouble();

        cManager.receive(factory.changeLatitude(*model->getDbManager(), oldLatitude, newLatitude, id));
    }

}

void Presenter::changeHeight(QItemSelectionModel *selection, double newHeight)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.first().row();
        QModelIndex index = model->getPoints()->index(row, 0);
        int id = model->getPoints()->data(index).toInt();
        index = model->getPoints()->index(row, 3);
        double oldHeight = model->getPoints()->data(index).toDouble();

        cManager.receive(factory.changeHeight(*model->getDbManager(), oldHeight, newHeight, id));
    }
}

void Presenter::createRoute()
{
    cManager.receive(factory.createRoute(*model->getDbManager()));
}

void Presenter::removeRoute(QItemSelectionModel *selection)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.front().row();
        int id = model->getRoutes()->data(model->getRoutes()->index(row, 0)).toInt();

        cManager.receive(factory.removeRoute(*model->getDbManager(), id));
    }
}

void Presenter::createPoint()
{
    cManager.receive(factory.createPoint(*model->getDbManager(), QGeoCoordinate(0, 0, 0)));
}

void Presenter::removePoint(QItemSelectionModel *selection)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.front().row();
        int id = model->getPoints()->data(model->getPoints()->index(row, 0)).toInt();

        cManager.receive(factory.removePoint(*model->getDbManager(), id));
    }
}

void Presenter::routeTableSelectionChanged(QModelIndex selected)
{
    QModelIndex data = model->getRoutes()->index(selected.row(), 0);
    model->getDbManager()->selectRoute(model->getRoutes()->data(data).toInt());

    data = model->getRoutes()->index(selected.row(), 1);
    emit currentName(model->getRoutes()->data(data).toString());
}

void Presenter::pointsTableSelectionChanged(QModelIndex selected)
{
    QModelIndex data = model->getPoints()->index(selected.row(), 1);
    double longitude = model->getPoints()->data(data).toDouble();
    data = model->getPoints()->index(selected.row(), 2);
    double latitude = model->getPoints()->data(data).toDouble();
    data = model->getPoints()->index(selected.row(), 3);
    double height = model->getPoints()->data(data).toDouble();

    emit currentPoint(longitude, latitude, height);
}

void Presenter::currentRouteChanged(int , int )
{
    model->getPoints()->setQuery(model->getDbManager()->pointsQuery());
}

void Presenter::readPolyline(const QString &filename)
{
    if(filename.isNull())
        return;


    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        emit sendError("Read polyline", "Can't read polyline file", EL_WARNING);

        return;
    }

    QTextStream stream(&file);
    QString polyline = stream.readAll();
    file.close();

    QVector<QGeoCoordinate> coordinates;
    PointsSaver saver(&coordinates);

    gpolyline::decode(polyline.toStdString(), &saver);

    cManager.receive(factory.importPolyline(filename.split("/").last().split(".").first(), coordinates, *model->getDbManager()));
}

void Presenter::writePolyline(const QString &filename)
{
    if(filename.isNull())
        return;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
    {
        emit sendError("Write polyline", "Can't write polyline file", EL_WARNING);

        return;
    }

    QTextStream stream(&file);
    QString polyline = "";

    int id = model->getDbManager()->getCurrentRoute();
    QVector<QGeoCoordinate> *coordinates = model->getDbManager()->getPoints(id);

    QGeoCoordinate previous(0, 0, 0);
    for(auto i : *coordinates)
    {
        QString tmp = gpolyline::encode(i.longitude() - previous.longitude(), i.latitude() - previous.latitude()).data();
        polyline += tmp;
        previous = i;
    }

    stream << polyline;
    file.close();
}

void Presenter::drawHeightMap(QItemSelectionModel *selection)
{
    QModelIndexList rows = selection->selectedIndexes();
    if(rows.size())
    {
        int row = rows.front().row();
        int id = model->getRoutes()->data(model->getRoutes()->index(row, 0)).toInt();

        QVector<QGeoCoordinate> *coords = model->getDbManager()->getPoints(id);

        int count = coords->count();
        QGeoCoordinate prev = coords->at(0);
        double len = 0;
        emit clearGraph();
        for(int i = 0; i < count; i++)
        {
            QGeoCoordinate current = coords->at(i);
            len += prev.distanceTo(current);
            emit addPointToGraph(len, current.altitude());
            prev = current;
        }
        emit displayGraph();

        delete coords;
    }
    else
        emit sendError("No selection", "No route is selected!", EL_INFO);
}

void Presenter::getPluginTable()
{
    if(pManager)
        emit sendPluginTable(pManager->getPluginTable());
}

void Presenter::createPluginManager()
{
    pThread = new QThread();
    pManager = new PluginManager(model);

    pManager->moveToThread(pThread);
    QObject::connect(pThread, SIGNAL(started()), pManager, SLOT(checkLoop()));

    pThread->start();
}
