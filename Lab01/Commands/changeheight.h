#ifndef CHANGEHEIGHT_H
#define CHANGEHEIGHT_H

#include "./command.h"
#include "../dbmanager.h"

class ChangeHeight : public Command
{
public:
    ChangeHeight(double oldHeight, double newHeight, int id, DBManager &manager);
    ~ChangeHeight() {}

    void exec() override;
    void reject() override;

private:
    double oldHeight;
    double newHeight;
    int id;
    DBManager &manager;
};

#endif // CHANGEHEIGHT_H
