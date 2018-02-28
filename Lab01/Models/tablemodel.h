#ifndef ROUTESMODEL_H
#define ROUTESMODEL_H

#include <QAbstractTableModel>
#include "abstractrow.h"

class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr);
    ~TableModel() {}

    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addHeader(QString header);
    void addEditableColumn(int col);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QVector<AbstractRow *> table;
    QVector<QString> headers;
    QVector<int> editableColumns;
};

#endif // ROUTESMODEL_H
