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
    Command *renameRoute(const QString &oldName, const QString &newName, DBManager &manager, int id);
    Command *reset(DBManager &manager);
    Command *createPoint(DBManager &manager, const QGeoCoordinate &coordinate);
    Command *removePoint(DBManager &manager, int id);
    Command *changeLongitude(DBManager &manager, double oldLongitude, double newLongitude, int id);
    Command *changeLatitude(DBManager &manager, double oldLatitude, double newLatitude, int id);
    Command *changeHeight(DBManager &manager, double oldHeight, double newHeight, int id);
    Command *importPolyline(const QString &name, QVector<QGeoCoordinate> &coordinates, DBManager &manager);

};

#endif // COMMANDFACTORY_H
