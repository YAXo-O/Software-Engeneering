#ifndef CHANGELONGITUDE_H
#define CHANGELONGITUDE_H

#include "./command.h"
#include "../dbmanager.h"

class ChangeLongitude: public Command
{
public:
    ChangeLongitude(double oldLongitude, double newLongitude, int id, DBManager &manager);
    ~ChangeLongitude() {}

    void exec() override;
    void reject() override;

private:
    DBManager &manager;
    double oldLongitude;
    double newLongitude;
    int id;
};

#endif // CHANGELONGITUDE_H
