#include "vectorrow.h"
#include "tablemodel.h"

TableModel::TableModel(int columns, QObject *parent): QAbstractTableModel(parent), column(columns)
{
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.count();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return column;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();


    if(orientation == Qt::Horizontal)
        return section < headers.count() ? headers[section] : QVariant();
    else
        return QString::number(section);

}

void TableModel::addHeader(QString header)
{
    headers.append(header);
}

void TableModel::addEditableColumn(int col)
{
    editableColumns.append(col);
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();

    return table.at(index.row())->getField(index.column());
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        table[(index.row())]->setField(index.column(), value);
        emit dataChanged(index, index);

        return true;
    }

    return false;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || count <= 0)
        return false;

    emit beginInsertRows(parent, row, row + count);

    for(int i = 0; i < count; i++)
    {
        VectorRow *elem = new VectorRow;

        table.insert(row + i, elem);
    }

    emit endInsertColumns();

    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || count <= 0 || row + count >= table.count())
        return false;

    emit beginRemoveRows(parent, row, row + count);

    for(int i = 0; i < count; i++)
        delete table[row + i];
    table.remove(row, count);

    emit endRemoveRows();

    return true;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    return editableColumns.contains(index.column()) ? (flags | Qt::ItemIsEditable) : flags;
}
