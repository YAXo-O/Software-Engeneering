#include "createroute.h"

CreateRoute::CreateRoute(DBManager &_manager): Command(), manager(_manager), id(-1)
{
}

void CreateRoute::exec()
{
    id = manager.addRoute("<unnamed>");
}

void CreateRoute::reject()
{
    manager.removeRoute(id);
}
