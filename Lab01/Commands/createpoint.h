#ifndef CREATEPOINT_H
#define CREATEPOINT_H

#include <QGeoCoordinate>

#include "./command.h"
#include "../dbmanager.h"

class CreatePoint : public Command
{
public:
    CreatePoint(DBManager &manager, const QGeoCoordinate &coordinate);
    ~CreatePoint() override {}

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    QGeoCoordinate coordinate;
    int id;
};

#endif // CREATEPOINT_H
