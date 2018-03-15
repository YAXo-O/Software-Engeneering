#include "removepoint.h"

RemovePoint::RemovePoint(DBManager &_manager, int _id):
    Command(), manager(_manager), id(_id)
{
}

void RemovePoint::exec()
{
    point = manager.getPoint(id);
    manager.removePoint(id);
}

void RemovePoint::reject()
{
    manager.restorePoint(point, id);
}
