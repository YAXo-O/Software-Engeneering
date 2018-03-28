#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class DBManager;
class QSqlQueryModel;

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    QSqlQueryModel *getRoutes() const;
    QSqlQueryModel *getPoints() const;
    DBManager *getDbManager() const;

    void setRoutes(QSqlQueryModel *routesModel);
    void setPoints(QSqlQueryModel *pointsModel);
    void setDbManager(DBManager *dbmanager);

    void init();

signals:
    void needsUpdate();

private:
    QSqlQueryModel *routes;
    QSqlQueryModel *points;
    DBManager *dbManager;
};

#endif // MODEL_H
