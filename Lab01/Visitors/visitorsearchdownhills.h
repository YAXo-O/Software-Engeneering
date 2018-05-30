#ifndef VISITORSEARCHDOWNHILLS_H
#define VISITORSEARCHDOWNHILLS_H

#include "abstractvisitor.h"

class VisitorSearchDownhills : public QObject, AbstractVisitor
{
    Q_OBJECT
    Q_INTERFACES(AbstractVisitor)
    //Q_PLUGIN_METADATA(IID "YAX.PPO.AbstractVisitor.Downhills" FILE "visitordownhills.json")

public:
    VisitorSearchDownhills() = default;
    ~VisitorSearchDownhills() override {}

    void operator()(Model &m) override;
};

#endif // VISITORSEARCHDOWNHILLS_H
