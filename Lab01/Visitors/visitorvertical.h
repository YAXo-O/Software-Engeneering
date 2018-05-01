#ifndef VISITORVERTICAL_H
#define VISITORVERTICAL_H

#include "abstractvisitor.h"

class VisitorVertical : public AbstractVisitor
{
public:
    VisitorVertical() = default;
    ~VisitorVertical() override {}

    void operator()(Model &m) override;
};

#endif // VISITORVERTICAL_H
