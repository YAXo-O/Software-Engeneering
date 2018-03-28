#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>

#include "presenter.h"

#include "model.h"

Presenter::Presenter(QObject *parent) : QObject(parent), model(nullptr), routesView(nullptr), pointsView(nullptr)
{
}

Model *Presenter::getModel() const
{
    return model;
}

void Presenter::setModel(Model *value)
{
    model = value;
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
    cManager.receive(factory.importFile(filename, *model->getDbManager()));
    /* TODO: catch exception and show message box in view */
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
    cManager.receive(factory.createPoint(*model->getDbManager(), QPointF(0, 0)));
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

    emit currentPoint(longitude, latitude);
}

void Presenter::currentRouteChanged(int , int )
{
    model->getPoints()->setQuery(model->getDbManager()->pointsQuery());
}
