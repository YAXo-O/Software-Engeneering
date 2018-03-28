#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include <QModelIndex>
#include <QItemSelectionModel>

#include "commandmanager.h"
#include "commandfactory.h"
#include "errorlevel.h"

class Model;
class QTableView;

class Presenter : public QObject
{
    Q_OBJECT
public:
    explicit Presenter(QObject *parent = nullptr);

    Model *getModel() const;
    QTableView *getRoutesView() const;
    QTableView *getPointsView() const;

    void setModel(Model *value);
    void setRoutesView(QTableView *value);
    void setPointsView(QTableView *value);

    void setConnections();

public slots:
    void loadFile(const QString &filename);
    void undo();
    void redo();
    void reset();
    void renameRoute(QItemSelectionModel *selection, const QString &newName);
    void changeLongitude(QItemSelectionModel *selection, double newLongitude);
    void changeLatitude(QItemSelectionModel *selection, double newLatitude);
    void createRoute();
    void removeRoute(QItemSelectionModel *selection);
    void createPoint();
    void removePoint(QItemSelectionModel *selection);

    void routeTableSelectionChanged(QModelIndex selected);
    void pointsTableSelectionChanged(QModelIndex selected);
    void currentRouteChanged(int old, int currnet);

    void readPolyline(const QString &filename);
    void writePolyline(const QString &filename);

signals:
    void currentName(const QString &name);
    void currentPoint(double longitude, double latitude);
    void sendError(const QString &title, const QString &message, errorLevel level);

private:
    Model *model;
    QTableView *routesView;
    QTableView *pointsView;
    CommandManager cManager;
    CommandFactory factory;

};

#endif // PRESENTER_H
