#include <QDebug>
#include <QDateTime>
#include <QGeoCoordinate>

#include "dbmanager.h"
#include "Visitors/abstractvisitor.h"

DBManager::DBManager(): QObject(), currentRoute(0), serial(0), bNotify(true)
{ 
    db = QSqlDatabase::addDatabase("QSQLITE");

    if(!db.open())
        qDebug() << db.lastError();

    QSqlQuery initRoutes;
    const QString initRoutesQuery = "CREATE TABLE "
                                    "routes("
                                    "id INTEGER PRIMARY KEY,"
                                    "name TEXT NOT NULL DEFAULT '<Empty>',"
                                    "len INT NOT NULL DEFAULT 0,"
                                    "creationDate TEXT NOT NULL)";


    QSqlQuery initPoints;
    const QString initPointsQuery = "CREATE TABLE "
                                    "points("
                                    "id INTEGER PRIMARY KEY,"
                                    "longitude REAL NOT NULL DEFAULT 0,"
                                    "latitude REAL NOT NULL DEFAULT 0,"
                                    "height REAL NOT NULL DEFAULT 0,"
                                    "route INTEGER NOT NULL DEFAULT 0,"
                                    "FOREIGN KEY(route) REFERENCES routes(id))";



    if(!initPoints.exec(initPointsQuery))
        qDebug() << "Points failure" << db.lastError();

    if(!initRoutes.exec(initRoutesQuery))
        qDebug() << "Routes failure" << db.lastError();
}

DBManager::~DBManager()
{
    if(db.isOpen())
        db.close();
}

int DBManager::addRoute(const QString &name)
{
    QSqlQuery insert;
    const QString insertQuery = "INSERT INTO routes(id, name, len, creationDate)"
                                "VALUES (?, ?, 0, ?)";

    currentRoute = serial++;
    insert.prepare(insertQuery);
    insert.bindValue(0, QString::number(currentRoute));
    insert.bindValue(1, name);
    insert.bindValue(2, QDateTime::currentDateTime().toLocalTime().toString());

    if(!insert.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();

    return currentRoute;
}

void DBManager::removeRoute(int id)
{
    QSqlQuery removePoints;
    const QString removePointsQuery = "DELETE FROM points WHERE route = ?";

    removePoints.prepare(removePointsQuery);
    removePoints.bindValue(0, QString::number(id));

    if(!removePoints.exec())
        qDebug() << db.lastError();

    QSqlQuery removeRoute;
    const QString removeRouteQuery = "DELETE FROM routes WHERE id = ?";

    removeRoute.prepare(removeRouteQuery);
    removeRoute.bindValue(0, QString::number(id));

    if(!removeRoute.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::setName(const QString &name)
{
    QSqlQuery update;
    const QString updateQuery = "UPDATE routes SET name = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, name);
    update.bindValue(1, QString::number(currentRoute));

    if(!update.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::rename(const QString &name, int id)
{
    QSqlQuery update;
    const QString updateQuery = "UPDATE routes SET name = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, name);
    update.bindValue(1, QString::number(id));

    if(!update.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

int DBManager::getCurrentRoute() const
{
    return currentRoute;
}

int DBManager::addPoint(const QGeoCoordinate &coordinate)
{
    if(currentRoute < 0)
        return -1;

    QSqlQuery insert;
    const QString insertQuery = "INSERT INTO points(longitude, latitude, height, route)"
                                "VALUES(?, ?, ?, ?)";

    insert.prepare(insertQuery);
    insert.bindValue(0, QString::number(coordinate.longitude()));
    insert.bindValue(1, QString::number(coordinate.latitude()));
    insert.bindValue(2, QString::number(coordinate.altitude()));
    insert.bindValue(3, QString::number(currentRoute));

    if(!insert.exec())
        qDebug() << db.lastError();

    recalcDistance(currentRoute);

    QSqlQuery returning;
    const QString returningQuery = "SELECT last_insert_rowid()";
    if(!returning.exec(returningQuery))
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();

    if(returning.next())
        return returning.value(0).toInt();

    return -1;
}

void DBManager::removePoint(int id)
{
    QSqlQuery select;
    const QString selectQuery = "SELECT route FROM points WHERE id = ?";

    select.prepare(selectQuery);
    select.bindValue(0, QString::number(id));

    if(!select.exec())
        qDebug() << db.lastError();

    int routeId = -1;
    if(!select.next())
        return;
    routeId = select.value(0).toInt();

    QSqlQuery remove;
    const QString removeQuery = "DELETE FROM points WHERE id = ?";

    remove.prepare(removeQuery);
    remove.bindValue(0, QString::number(id));

    if(!remove.exec())
        qDebug() << db.lastError();

    recalcDistance(routeId);

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::restorePoint(const QGeoCoordinate &coordinate, int id)
{
    if(currentRoute < 0)
        return;

    QSqlQuery insert;
    const QString insertQuery = "INSERT INTO points(id, longitude, latitude, height, route)"
                                "VALUES(?, ?, ?, ?, ?)";

    insert.prepare(insertQuery);
    insert.bindValue(0, QString::number(id));
    insert.bindValue(1, QString::number(coordinate.longitude()));
    insert.bindValue(2, QString::number(coordinate.latitude()));
    insert.bindValue(3, QString::number(coordinate.altitude()));
    insert.bindValue(4, QString::number(currentRoute));

    if(!insert.exec())
        qDebug() << db.lastError();

    recalcDistance(currentRoute);

    if(bNotify)
        emit needsRefreshment();
}

QGeoCoordinate DBManager::getPoint(int id)
{
    QSqlQuery select;
    QString selectQuery = "SELECT longitude, latitude, height FROM points WHERE id = " + QString::number(id);

    if(!select.exec(selectQuery))
        qDebug() << db.lastError();

    if(select.next())
        return QGeoCoordinate(select.value(0).toDouble(), select.value(1).toDouble(), select.value(2).toDouble());

    return QGeoCoordinate();
}

QVector<QGeoCoordinate> *DBManager::getPoints(int routeId)
{
    QSqlQuery select;
    QString selectQuery = "SELECT longitude, latitude, height FROM points WHERE route = " + QString::number(routeId);

    if(!select.exec(selectQuery))
        qDebug() << db.lastError();

    QVector<QGeoCoordinate> *result = new QVector<QGeoCoordinate>;
    while(select.next())
        result->append(QGeoCoordinate(select.value(1).toDouble(), select.value(0).toDouble(), select.value(2).toDouble()));

    return result;
}

void DBManager::changeLongitude(double value, int id)
{
    /*
    QSqlQuery select;
    const QString selectQuery = "SELECT route FROM points WHERE id = ?";

    select.prepare(selectQuery);
    select.bindValue(0, QString::number(id));

    if(!select.exec())
        qDebug() << db.lastError();

    int routeId = -1;
    if(!select.next())
        return;
    routeId = select.value(0).toInt();
    */

    QSqlQuery update;
    const QString updateQuery = "UPDATE points SET longitude = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, QString::number(value));
    update.bindValue(1, QString::number(id));

    if(!update.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::changeLatitude(double value, int id)
{
    QSqlQuery update;
    const QString updateQuery = "UPDATE points SET latitude = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, QString::number(value));
    update.bindValue(1, QString::number(id));

    if(!update.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::changeHeight(double value, int id)
{
    QSqlQuery update;
    const QString updateQuery = "UPDATE points SET height = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, QString::number(value));
    update.bindValue(1, QString::number(id));

    if(!update.exec())
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();

}

QString DBManager::routeQuery() const
{
    return "SELECT id, name AS Name, len AS 'Route Length', creationDate AS 'Creation Date' FROM routes";
}

QString DBManager::pointsQuery() const
{
    return "SELECT id, longitude AS 'Longitude', latitude AS 'Latitude', height as 'Height'"
           "FROM points WHERE route = " + QString::number(currentRoute);
}

void DBManager::disableNotifications()
{
    bNotify = false;
}

void DBManager::enableNotifications()
{
    bNotify = true;
}

void DBManager::refresh()
{
    emit needsRefreshment();
}

void DBManager::reset()
{
    QSqlQuery dropRoutes;
    const QString dropRoutesQuery = "DELETE FROM routes";
    QSqlQuery dropPoints;
    const QString dropPointsQuery = "DELETE FROM points";

    if(!dropPoints.exec(dropPointsQuery) || !dropRoutes.exec(dropRoutesQuery))
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::backupRoute(int id)
{
    const QString routeTableBackup = routeCopyPrefix + QString::number(id);
    const QString pointsTableBackup = pointsCopyPrefix + QString::number(id);

    QSqlQuery createBackupRuote;
    QString createRouteBackupQuery =    "CREATE TABLE IF NOT EXISTS " + routeTableBackup +
                                        "(id INTEGER PRIMARY KEY,"
                                        "name TEXT NOT NULL DEFAULT '<Empty>',"
                                        "len INT NOT NULL DEFAULT 0,"
                                        "creationDate TEXT NOT NULL)";
    QSqlQuery createBackupPoints;
    QString createPointsBackupQuery =   "CREATE TABLE IF NOT EXISTS " + pointsTableBackup +
                                        "(id INTEGER PRIMARY KEY,"
                                        "longitude REAL NOT NULL DEFAULT 0,"
                                        "latitude REAL NOT NULL DEFAULT 0,"
                                        "height REAL NOT NULL DEFAULT 0,"
                                        "route INTEGER NOT NULL DEFAULT 0)";

    if(!createBackupRuote.exec(createRouteBackupQuery) || !createBackupPoints.exec(createPointsBackupQuery))
        qDebug() << "Error at creating table" << db.lastError();

    QSqlQuery copyRoute;
    QString copyRouteQuery = "INSERT INTO " + routeTableBackup + " SELECT * FROM routes WHERE id = " + QString::number(id);
    QSqlQuery copyPoints;
    QString copyPointsQuery =
            "INSERT INTO " + pointsTableBackup + " SELECT * FROM points WHERE route = " + QString::number(id);

    if(!copyRoute.exec(copyRouteQuery) || !copyPoints.exec(copyPointsQuery))
        qDebug() << "Error at copying data" << db.lastError();
}

void DBManager::restoreRoute(int id)
{
    const QString routeTableBackup = routeCopyPrefix + QString::number(id);
    const QString pointsTableBackup = pointsCopyPrefix + QString::number(id);

    QSqlQuery copyRoute;
    QString copyRouteQuery = "INSERT INTO routes SELECT * FROM " + routeTableBackup + " WHERE id = " + QString::number(id);
    QSqlQuery copyPoints;
    QString copyPointsQuery =
            "INSERT INTO points SELECT * FROM " + pointsTableBackup + " WHERE route = " + QString::number(id);

    if(!copyRoute.exec(copyRouteQuery) || !copyPoints.exec(copyPointsQuery))
        qDebug() << db.lastError();

    if(bNotify)
        emit needsRefreshment();
}

void DBManager::dropBackup(int id)
{
    QSqlQuery dropRoutes;
    const QString dropRoutesQuery = "DELETE FROM " + routeCopyPrefix + QString::number(id);
    QSqlQuery dropPoints;
    const QString dropPointsQuery = "DELETE FROM " + pointsCopyPrefix + QString::number(id);

    if(!dropPoints.exec(dropPointsQuery) || !dropRoutes.exec(dropRoutesQuery))
        qDebug() << db.lastError();
}

void DBManager::recalcDistance(int id)
{
    return;

    QSqlQuery select;
    const QString selectQuery = "SELECT longitude, latitude, height FROM points WHERE route = " + QString::number(id);

    if(!select.exec(selectQuery))
        qDebug() << db.lastError();

    double len = 0;

    if(select.next())
    {
        QGeoCoordinate previous(select.value(1).toDouble(), select.value(0).toDouble(), select.value(2).toDouble());
        while(select.next())
        {
            QGeoCoordinate current(select.value(1).toDouble(), select.value(0).toDouble(), select.value(2).toDouble());
            len += previous.distanceTo(current);
            previous = current;
        }
    }

    QSqlQuery update;
    const QString updateQuery = "UPDATE routes SET len = ? WHERE id = ?";

    update.prepare(updateQuery);
    update.bindValue(0, QString::number(len));
    update.bindValue(1, QString::number(id));
}

void DBManager::acceptVisitor(AbstractVisitor *visitor)
{
    if(visitor)
        visitor->operator()(*this);
}

void DBManager::selectRoute(int id)
{
    int previous = currentRoute;
    currentRoute = id;
    emit selectionChanged(previous, currentRoute);
}


