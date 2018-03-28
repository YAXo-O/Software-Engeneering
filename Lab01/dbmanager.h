#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QString>
#include <QPointF>
#include <QtSql>

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

    int addPoint(const QPointF &point);
    void removePoint(int id);
    void restorePoint(const QPointF &point, int id);
    QPointF getPoint(int id);
    QVector<QPointF> *getPoints(int routeId);
    void changeLongitude(double value, int id);
    void changeLatitude(double value, int id);

    QString routeQuery() const;
    QString pointsQuery() const;

    void disableNotifications();
    void enableNotifications();
    void refresh();

    void reset();

    void backupRoute(int id);
    void restoreRoute(int id);
    void dropBackup(int id);

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
