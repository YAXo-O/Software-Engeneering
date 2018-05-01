#include "changeheight.h"

ChangeHeight::ChangeHeight(double _oldHeight, double _newHeight, int _id, DBManager &_manager):
    oldHeight(_oldHeight), newHeight(_newHeight), id(_id), manager(_manager)
{
}

void ChangeHeight::exec()
{
    manager.changeHeight(newHeight, id);
}

void ChangeHeight::reject()
{
    manager.changeHeight(oldHeight, id);
}
