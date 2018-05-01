#include "createpoint.h"

CreatePoint::CreatePoint(DBManager &_manager, const QGeoCoordinate &_coordinate):
    Command(), manager(_manager), coordinate(_coordinate), id(-1)
{
}

void CreatePoint::exec()
{
    if(id == -1)
        id = manager.addPoint(coordinate);
    else
        manager.restorePoint(coordinate, id);

}

void CreatePoint::reject()
{
    manager.removePoint(id);
}
