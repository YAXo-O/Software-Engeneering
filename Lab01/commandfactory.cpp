#include "commandfactory.h"
#include "Commands/import.h"
#include "Commands/createroute.h"
#include "Commands/removeroute.h"
#include "Commands/reset.h"

Command *CommandFactory::importFile(const QString &filename, DBManager &manager)
{
    return new Import(filename, manager);
}

Command *CommandFactory::createRoute(DBManager &manager)
{
    return new CreateRoute(manager);
}

Command *CommandFactory::removeRoute(DBManager &manager, int id)
{
    return new RemoveRoute(manager, id);
}

Command *CommandFactory::reset(DBManager &manager)
{
    return new Reset(manager);
}
