#include <QSqlQueryModel>
#include <QTableView>

#include "model.h"

#include "dbmanager.h"
#include "Visitors/abstractvisitor.h"

Model::Model(QObject *parent) : QObject(parent), routes(nullptr), points(nullptr), dbManager(nullptr)
{
}

QSqlQueryModel *Model::getRoutes() const
{
    return routes;
}

void Model::setRoutes(QSqlQueryModel *value)
{
    routes = value;
}

QSqlQueryModel *Model::getPoints() const
{
    return points;
}

void Model::setPoints(QSqlQueryModel *value)
{
    points = value;
}

DBManager *Model::getDbManager() const
{
    return dbManager;
}

void Model::setDbManager(DBManager *value)
{
    dbManager = value;

    connect(dbManager, SIGNAL(needsRefreshment()), SIGNAL(needsUpdate()));
}

void Model::init()
{
    setDbManager(new DBManager());
    routes = new QSqlQueryModel();
    points = new QSqlQueryModel();

    routes->setQuery(dbManager->routeQuery());
    points->setQuery(dbManager->pointsQuery());
}

void Model::receiveVisitor(AbstractVisitor *visitor)
{
    dbManager->acceptVisitor(visitor);
}
