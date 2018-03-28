#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QItemSelectionModel>

#include "errorlevel.h"

namespace Ui {
    class MainWindow;
}

class Presenter;
class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTableView *getRoutesView() const;
    QTableView *getPointsView() const;

    void setConnections();

public slots:
    void currentRoute(const QString &name);
    void currentPoint(double longitude, double latitude);

    void receiveError(const QString &title, const QString &message, errorLevel level);

signals:
    void loadFile(const QString &filename);
    void undo();
    void redo();
    void doReset();
    void renameRoute(QItemSelectionModel *selection, const QString &newName);
    void changeLongitude(QItemSelectionModel *selection, double newLongitude);
    void changeLatitude(QItemSelectionModel *selection, double newLatitude);
    void createRoute();
    void removeRoute(QItemSelectionModel *selection);
    void createPoint();
    void removePoint(QItemSelectionModel *selection);

    void routeTableSelectionChanged(QModelIndex selected);
    void pointsTableSelectionChanged(QModelIndex selected);

    void readPolyline(const QString &filename);
    void writePolyline(const QString &filename);

private slots:
    void onActionloadTriggered();
    void onActionresetTriggered();
    void onActioncreaterouteTriggered();
    void onActionupdatepolylineTriggered();

private:
    Ui::MainWindow *ui;

    void setValidators();
};

#endif // MAINWINDOW_H
