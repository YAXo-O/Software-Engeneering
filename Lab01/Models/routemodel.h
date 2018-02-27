#ifndef ROUTEMODEL_H
#define ROUTEMODEL_H

#include <QAbstractItemModel>

class RouteModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    RouteModel();

    QVariant data(const QModelIndex &index, int nRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int nRole);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // ROUTEMODEL_H
