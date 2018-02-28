#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TableModel;
class RoutesManager;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setModels(TableModel *routes, TableModel *points);
    void setRoutesManager(RoutesManager *man);

private:
    Ui::MainWindow *ui;
    RoutesManager *manager;

    void setValidators();
};

#endif // MAINWINDOW_H
