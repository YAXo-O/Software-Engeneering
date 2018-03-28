#include "commandfactory.h"
#include "Commands/import.h"
#include "Commands/createroute.h"
#include "Commands/removeroute.h"
#include "Commands/reset.h"
#include "Commands/createpoint.h"
#include "Commands/removepoint.h"
#include "Commands/renameroute.h"
#include "Commands/changelongitude.h"
#include "Commands/changelatitude.h"

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

Command *CommandFactory::renameRoute(const QString &oldName, const QString &newName, DBManager &manager, int id)
{
    return new RenameRoute(oldName, newName, id, manager);
}

Command *CommandFactory::reset(DBManager &manager)
{
    return new Reset(manager);
}

Command *CommandFactory::createPoint(DBManager &manager, const QPointF &point)
{
    return new CreatePoint(manager, point);
}

Command *CommandFactory::removePoint(DBManager &manager, int id)
{
    return new RemovePoint(manager, id);
}

Command *CommandFactory::changeLongitude(DBManager &manager, double oldLongitude, double newLongitude, int id)
{
    return new ChangeLongitude(oldLongitude, newLongitude, id, manager);
}

Command *CommandFactory::changeLatitude(DBManager &manager, double oldLatitude, double newLatitude, int id)
{
    return new ChangeLatitude(oldLatitude, newLatitude, id, manager);
}
