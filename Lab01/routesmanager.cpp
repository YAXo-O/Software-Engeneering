#include <QDateTime>

#include "routesmanager.h"

RoutesManager::RoutesManager(): routes(new TableModel), points(new TableModel), current(0), serial(0)
{
    routes->addHeader("Name");
    routes->addHeader("Length");
    routes->addHeader("Creation time");
    routes->addEditableColumn(0);

    points->addHeader("№");
    points->addHeader("Longitude");
    points->addHeader("Latitude");
    points->addEditableColumn(1);
    points->addEditableColumn(2);
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
