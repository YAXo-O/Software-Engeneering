#include <QVector>
#include <QPointF>

#include "importpolyline.h"

#include "../dbmanager.h"

ImportPolyline::ImportPolyline(const QString &_name, QVector<QGeoCoordinate> &_coordinates, DBManager &_manager): Command(),
   name(_name), coordinates(_coordinates), manager(_manager)
{
}

void ImportPolyline::exec()
{
    manager.addRoute(name);
    for(auto i : coordinates)
        manager.addPoint(i);
}

void ImportPolyline::reject()
{
}

bool ImportPolyline::isUndoable()
{
    return false;
}
