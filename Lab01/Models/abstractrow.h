#ifndef ABSTRACTROW_H
#define ABSTRACTROW_H

#include <QVariant>

class AbstractRow
{
public:
    AbstractRow() {}
    virtual ~AbstractRow() {}

    virtual void setField(int field, const QVariant &value) = 0;
    virtual QVariant getField(int field) const = 0;
};

#endif // ABSTRACTROW_H
