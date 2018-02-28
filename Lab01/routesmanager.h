#ifndef ROUTESMANAGER_H
#define ROUTESMANAGER_H

#include <QString>
#include "Models/tablemodel.h"

class RoutesManager
{
public:
    RoutesManager();
    ~RoutesManager() = default;

    void addRoute(const QString &name);
    void selectRoute(uint16_t id);
    void addPoint(double longitude, double latitude);
    void removePoint(uint16_t id);
    void changePoint(uint16_t id, double longitude, double latitude);

    TableModel *routesModel() const;
    TableModel *pointsModel() const;

private:
    TableModel *routes;
    TableModel *points;

    uint16_t current;
    uint16_t serial;

};

#endif // ROUTESMANAGER_H
