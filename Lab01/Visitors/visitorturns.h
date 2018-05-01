#ifndef VISITORTURNS_H
#define VISITORTURNS_H

#include "abstractvisitor.h"

class VisitorTurns : public AbstractVisitor
{
public:
    VisitorTurns() = default;
    ~VisitorTurns() override {}

    void operator()(Model &m) override;
};

#endif // VISITORTURNS_H
