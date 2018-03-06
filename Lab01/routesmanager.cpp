#include <QDateTime>

#include <QDebug>

#include "routesmanager.h"

RoutesManager::RoutesManager(): routes(new TableModel(3)), points(new TableModel(2)), current(0), serial(0)
{
    routes->addHeader("Name");
    routes->addHeader("Length");
    routes->addHeader("Creation time");
    routes->addEditableColumn(0);

    points->addHeader("Longitude");
    points->addHeader("Latitude");
    points->addEditableColumn(0);
    points->addEditableColumn(1);
}

void RoutesManager::addRoute(const QString &name)
{
    current = serial++;
    int row = routes->rowCount();
    routes->insertRow(row);
    routes->setData(routes->index(row, 0), name);
    routes->setData(routes->index(row, 1), 0);
    routes->setData(routes->index(row, 2), QDateTime::currentDateTime());
    routes->setData(routes->index(row, 3), current);
}

void RoutesManager::selectRoute(uint16_t id)
{
    current = id;
}

void RoutesManager::addPoint(double longitude, double latitude)
{
    int row = points->rowCount();
    points->insertRow(row);
    points->setData(points->index(row, 0), longitude);
    points->setData(points->index(row, 1), latitude);
    points->setData(points->index(row, 2), current);
}

void RoutesManager::removePoint(uint16_t id)
{
}

void RoutesManager::changePoint(uint16_t id, double longitude, double latitude)
{
}

TableModel *RoutesManager::routesModel() const
{
    return routes;
}

TableModel *RoutesManager::pointsModel() const
{
    return points;
}
