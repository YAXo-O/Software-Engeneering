#ifndef REMOVEPOINT_H
#define REMOVEPOINT_H

#include <QGeoCoordinate>

#include "command.h"
#include "./dbmanager.h"

class RemovePoint : public Command
{
public:
    RemovePoint(DBManager &manager, int id);
    ~RemovePoint() override {}

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    QGeoCoordinate coordinate;
    int id;
};

#endif // REMOVEPOINT_H
