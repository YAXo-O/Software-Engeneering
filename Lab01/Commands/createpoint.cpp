#include "createpoint.h"

CreatePoint::CreatePoint(DBManager &_manager, const QPointF &_point): Command(), manager(_manager), point(_point), id(-1)
{
}

void CreatePoint::exec()
{
    if(id == -1)
        id = manager.addPoint(point);
    else
        manager.restorePoint(point, id);

}

void CreatePoint::reject()
{
    manager.removePoint(id);
}
