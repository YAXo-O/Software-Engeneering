#include "command.h"

Command::~Command()
{
}

bool Command::isUndoable()
{
    return true;
}
