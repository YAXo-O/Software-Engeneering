#include "vectorrow.h"

VectorRow::VectorRow()
{
}

QVariant VectorRow::getField(int field) const
{
    if(field >= row.count())
        return QVariant();

    return row[field];
}

void VectorRow::setField(int field, const QVariant &value)
{
    if(field >= row.count())
        row.resize(field + 1);

    row[field] = value;
}
