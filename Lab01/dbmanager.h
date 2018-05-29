#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QString>
#include <QtSql>
#include <QGeoCoordinate>

const QString routeCopyPrefix = "routeCopy";
const QString pointsCopyPrefix = "pointsCopy";

class DBManager: public QWidget
{
    Q_OBJECT
public:
    DBManager();
    ~DBManager();

    int addRoute(const QString &name);
    void removeRoute(int id);
    void setName(const QString &name);
    void rename(const QString &name, int id);
    int getCurrentRoute() const;

    int addPoint(const QGeoCoordinate &coordinate);
    void removePoint(int id);
    void restorePoint(const QGeoCoordinate &coordinate, int id);
    QGeoCoordinate getPoint(int id);
    QVector<QGeoCoordinate> *getPoints(int routeId);
    void changeLongitude(double value, int id);
    void changeLatitude(double value, int id);
    void changeHeight(double value, int id);

    QString routeQuery() const;
    QString pointsQuery() const;

    void disableNotifications();
    void enableNotifications();
    void refresh();

    void reset();

    void backupRoute(int id);
    void restoreRoute(int id);
    void dropBackup(int id);

    void recalcDistance(int id);

public slots:
    void selectRoute(int id);

private:
    QSqlDatabase db;
    int currentRoute;
    int serial;
    bool bNotify;

signals:
    void needsRefreshment();
    void routeChanged(int id);
    void pointChanged(int id);
    void selectionChanged(int previous, int current);
};

#endif // DBMANAGER_H
