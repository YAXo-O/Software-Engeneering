#ifndef ABSTRACTVISITOR_H
#define ABSTRACTVISITOR_H

class Model;

class AbstractVisitor
{
public:
    AbstractVisitor() = default;
    virtual ~AbstractVisitor() {}

    virtual void operator()(Model &m) = 0;
};

#endif // ABSTRACTVISITOR_H
