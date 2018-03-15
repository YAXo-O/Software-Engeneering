#ifndef CREATEROUTE_H
#define CREATEROUTE_H

#include "./command.h"
#include "../dbmanager.h"

class CreateRoute: public Command
{
public:
    CreateRoute(DBManager &manager);
    ~CreateRoute() override {}

    void exec();
    void reject();

private:
    DBManager &manager;
    int id;
};

#endif // CREATEROUTE_H
