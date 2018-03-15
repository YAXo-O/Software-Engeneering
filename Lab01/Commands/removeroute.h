#ifndef REMOVEROUTE_H
#define REMOVEROUTE_H

#include <QString>
#include "./command.h"
#include "../dbmanager.h"

class RemoveRoute : public Command
{
public:
    RemoveRoute(DBManager &manager, int id);
    ~RemoveRoute() override;

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    int id;
};

#endif // REMOVEROUTE_H
