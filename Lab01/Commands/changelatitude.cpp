#include "changelatitude.h"

ChangeLatitude::ChangeLatitude(double _oldLatitude, double _newLatitude, int _id, DBManager &_manager): Command(),
    manager(_manager), oldLatitude(_oldLatitude), newLatitude(_newLatitude), id(_id)
{
}

void ChangeLatitude::exec()
{
    manager.changeLatitude(newLatitude, id);
}

void ChangeLatitude::reject()
{
    manager.changeLatitude(oldLatitude, id);
}
