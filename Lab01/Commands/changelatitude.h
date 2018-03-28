#ifndef CHANGELATITUDE_H
#define CHANGELATITUDE_H

#include "./command.h"
#include "../dbmanager.h"

class ChangeLatitude : public Command
{
public:
    ChangeLatitude(double oldLatitude, double newLatitude, int id, DBManager &manager);
    ~ChangeLatitude() {}

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    double oldLatitude;
    double newLatitude;
    int id;
};

#endif // CHANGELATITUDE_H
