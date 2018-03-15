#include "reset.h"

Reset::Reset(DBManager &_manager): Command(), manager(_manager)
{
}

void Reset::exec()
{
    manager.reset();
}

void Reset::reject()
{
}

bool Reset::isUndoable()
{
    return false;
}
