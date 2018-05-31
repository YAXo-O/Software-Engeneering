#include "visitorturns.h"
#include "../dbmanager.h"

#include <QDebug>

void VisitorTurns::operator()(DBManager &m)
{
    qDebug() << m.getCurrentRoute();
}
