#include "removepoint.h"

RemovePoint::RemovePoint(DBManager &_manager, int _id):
    Command(), manager(_manager), id(_id)
{
}

void RemovePoint::exec()
{
    coordinate = manager.getPoint(id);
    manager.removePoint(id);
}

void RemovePoint::reject()
{
    manager.restorePoint(coordinate, id);
}
