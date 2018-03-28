#include <QVector>
#include <QPointF>

#include "importpolyline.h"

#include "../dbmanager.h"

ImportPolyline::ImportPolyline(const QString &_name, QVector<QPointF> &_points, DBManager &_manager): Command(),
   name(_name), points(_points), manager(_manager)
{
}

void ImportPolyline::exec()
{
    manager.addRoute(name);
    for(auto i : points)
        manager.addPoint(i);
}

void ImportPolyline::reject()
{
}

bool ImportPolyline::isUndoable()
{
    return false;
}
