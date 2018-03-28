#include "changelongitude.h"

ChangeLongitude::ChangeLongitude(double _oldLongitude, double _newLongitude, int _id, DBManager &_manager): Command(),
    manager(_manager), oldLongitude(_oldLongitude), newLongitude(_newLongitude), id(_id)
{
}

void ChangeLongitude::exec()
{
    manager.changeLongitude(newLongitude, id);
}

void ChangeLongitude::reject()
{
    manager.changeLongitude(oldLongitude, id);
}
