#ifndef REMOVEPOINT_H
#define REMOVEPOINT_H

#include <QPointF>

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
    QPointF point;
    int id;
};

#endif // REMOVEPOINT_H
