#ifndef VISITORTURNS_H
#define VISITORTURNS_H

#include "abstractvisitor.h"

class VisitorTurns : public QObject, public AbstractVisitor
{
    Q_OBJECT
    Q_INTERFACES(AbstractVisitor)
    Q_PLUGIN_METADATA(IID "YAX.PPO.AbstractVisitor" FILE "visitorturns.json")

public:
    VisitorTurns() = default;
    ~VisitorTurns() override {}

    void operator()(DBManager &m) override;
};

#endif // VISITORTURNS_H
