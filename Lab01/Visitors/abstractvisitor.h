#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

#include <QtPlugin>

class DBManager;

class AbstractVisitor
{
public:
    AbstractVisitor() = default;
    virtual ~AbstractVisitor() {}

    virtual void operator()(DBManager &m) = 0;
};

Q_DECLARE_INTERFACE(AbstractVisitor, "YAX.PPO.AbstractVisitor")

#endif // ABSTRACTVISITOR_H
