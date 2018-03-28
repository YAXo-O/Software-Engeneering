#include "renameroute.h"

RenameRoute::RenameRoute(const QString &_oldName, const QString &_newName, int _id, DBManager &_manager): Command(),
    oldName(_oldName), newName(_newName), manager(_manager), id(_id)
{
}

void RenameRoute::exec()
{
    manager.rename(newName, id);
}

void RenameRoute::reject()
{
    manager.rename(oldName, id);
}
