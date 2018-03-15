#include "removeroute.h"

RemoveRoute::RemoveRoute(DBManager &_manager, int _id): Command(), manager(_manager), id(_id)
{
}

RemoveRoute::~RemoveRoute()
{
    manager.dropBackup(id);
}

void RemoveRoute::exec()
{
    manager.dropBackup(id);
    manager.backupRoute(id);
    manager.removeRoute(id);
}

void RemoveRoute::reject()
{
    manager.restoreRoute(id);
}
