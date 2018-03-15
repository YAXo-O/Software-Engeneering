#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <QString>
#include "Commands/command.h"
#include "dbmanager.h"

class CommandFactory
{
public:
    CommandFactory() = default;
    ~CommandFactory() = default;

    Command *importFile(const QString &filename, DBManager &manager);
    Command *createRoute(DBManager &manager);
    Command *removeRoute(DBManager &manager, int id);
    Command *reset(DBManager &manager);
    Command *createPoint(DBManager &manager, const QPointF &point);
    Command *removePoint(DBManager &manager, int id);

};

#endif // COMMANDFACTORY_H
