#include "Models/tablemodel.h"
#include "routesmanager.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), manager(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModels(TableModel *routes, TableModel *points)
{
    ui->routeTableView->setModel(routes);
    ui->pointTableView->setModel(points);
}

void MainWindow::setRoutesManager(RoutesManager *man)
{
    manager = man;
    setModels(manager->routesModel(), manager->pointsModel());
}
