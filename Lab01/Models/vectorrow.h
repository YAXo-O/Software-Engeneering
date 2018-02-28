#ifndef VECTORROW_H
#define VECTORROW_H

#include <QVector>
#include <QVariant>

#include "abstractrow.h"

class VectorRow : public AbstractRow
{
public:
    VectorRow();
    ~VectorRow() {}

    virtual void setField(int field, const QVariant &value) override;
    virtual QVariant getField(int field) const override;

private:
    QVector<QVariant> row;
};

#endif // VECTORROW_H
