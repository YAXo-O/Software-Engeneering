#ifndef VISITORSEARCHDOWNHILLS_H
#define VISITORSEARCHDOWNHILLS_H

#include "abstractvisitor.h"

class VisitorSearchDownhills : public AbstractVisitor
{
public:
    VisitorSearchDownhills() = default;
    ~VisitorSearchDownhills() override {}

    void operator()(Model &m) override;
};

#endif // VISITORSEARCHDOWNHILLS_H
