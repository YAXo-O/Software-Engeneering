#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbmanager.h"
#include "commandmanager.h"
#include "commandfactory.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onActionloadTriggered();
    void onActionundoTriggered();

    void onActionredoTriggered();

    void onActionresetTriggered();

private:
    Ui::MainWindow *ui;
    DBManager manager;
    CommandManager cmd;
    CommandFactory factory;
    QSqlQueryModel routes;
    QSqlQueryModel points;

    void setValidators();
    void setConnections();
};

#endif // MAINWINDOW_H
