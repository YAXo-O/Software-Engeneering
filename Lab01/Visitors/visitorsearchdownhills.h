#ifndef VISITORSEARCHDOWNHILLS_H
#define VISITORSEARCHDOWNHILLS_H

#include <QGeoCoordinate>

#include "abstractvisitor.h"

class VisitorSearchDownhills : public QObject, AbstractVisitor
{
    Q_OBJECT
    Q_INTERFACES(AbstractVisitor)
    Q_PLUGIN_METADATA(IID "YAX.PPO.AbstractVisitor.Downhills" FILE "visitordownhills.json")

public:
    VisitorSearchDownhills() = default;
    ~VisitorSearchDownhills() override {}

    void operator()(DBManager &m) override;

private:
    void putType(unsigned int typeAngle[], unsigned int typeLen[], double angle, double len);
};

#endif // VISITORSEARCHDOWNHILLS_H
