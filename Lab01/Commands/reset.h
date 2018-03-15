#ifndef RESET_H
#define RESET_H

#include "command.h"
#include "../dbmanager.h"

class Reset: public Command
{
public:
    Reset(DBManager &manager);
    ~Reset() override {}

    void exec() override;
    void reject() override;

    bool isUndoable() override;

private:
    DBManager &manager;
};

#endif // RESET_H
