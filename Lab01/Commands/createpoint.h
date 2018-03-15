#ifndef CREATEPOINT_H
#define CREATEPOINT_H

#include <QPointF>

#include "./command.h"
#include "../dbmanager.h"

class CreatePoint : public Command
{
public:
    CreatePoint(DBManager &manager, const QPointF &point);
    ~CreatePoint() override {}

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    QPointF point;
    int id;
};

#endif // CREATEPOINT_H
