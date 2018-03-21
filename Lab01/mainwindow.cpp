#include <QFileDialog>
#include <QMessageBox>

#include "Parsers/gpxparser.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Tables setup
    ui->routeTableView->setModel(&routes);
    ui->pointTableView->setModel(&points);
    ui->routeTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    setValidators();
    setConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onActionloadTriggered()
{
    QStringList filename = QFileDialog::getOpenFileNames(nullptr, "GPX File", QString(), "*.gpx");
    if(filename.isEmpty())
        return;
    try
    {
        for(auto i : filename)
            cmd.Receive(factory.importFile(i, manager));
    }
    catch(std::exception &e)
    {
        QMessageBox::information(nullptr, "Read file error", e.what());
    }
}

void MainWindow::setConnections()
{
    // Table selection
    connect(ui->routeTableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            [this](QModelIndex selected, QModelIndex)
    {
        QModelIndex data = routes.index(selected.row(), 0);
        manager.selectRoute(routes.data(data).toInt());

        data = routes.index(selected.row(), 1);
        ui->routeNameLine->setText(routes.data(data).toString());
    });
    connect(ui->pointTableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            [this](QModelIndex selected, QModelIndex)
    {
        QModelIndex data = points.index(selected.row(), 1);
        ui->longitudeLine->setText(points.data(data).toString());

        data = points.index(selected.row(), 2);
        ui->latitudeLine->setText(points.data(data).toString());
    });

    // Data user changed
    connect(ui->routeNameLine, &QLineEdit::returnPressed, [this]()
    {
        QItemSelectionModel *selection = ui->routeTableView->selectionModel();
        QModelIndexList rows = selection->selectedIndexes();
        if(rows.size())
        {
            int row = rows.first().row();
            QModelIndex index = routes.index(row, 0);

            manager.rename(ui->routeNameLine->text(), routes.data(index).toInt());
        }
    });
    connect(ui->longitudeLine, &QLineEdit::returnPressed, [this]()
    {
        QItemSelectionModel *selection = ui->pointTableView->selectionModel();
        QModelIndexList rows = selection->selectedIndexes();
        if(rows.size())
        {
            int row = rows.first().row();
            QModelIndex index = points.index(row, 0);

            manager.changeLongitude(ui->longitudeLine->text().toDouble(), points.data(index).toInt());
        }
    });
    connect(ui->latitudeLine, &QLineEdit::returnPressed, [this]()
    {
        QItemSelectionModel *selection = ui->pointTableView->selectionModel();
        QModelIndexList rows = selection->selectedIndexes();
        if(rows.size())
        {
            int row = rows.first().row();
            QModelIndex index = points.index(row, 0);

            manager.changeLatitude(ui->latitudeLine->text().toDouble(), points.data(index).toInt());
        }
    });

    // Manager selection changed
    connect(&manager, &DBManager::selectionChanged, [this](int , int)
    {
       points.setQuery(manager.pointsQuery());
    });

    connect(&manager, &DBManager::needsRefreshment, [this]()
    {
        routes.setQuery(manager.routeQuery());
        points.setQuery(manager.pointsQuery());
    });

    // Actions connections
    connect(ui->actionLoad, SIGNAL(triggered()), SLOT(onActionloadTriggered()));
    connect(ui->actionUndo, SIGNAL(triggered()), SLOT(onActionundoTriggered()));
    connect(ui->actionRedo, SIGNAL(triggered()), SLOT(onActionredoTriggered()));
    connect(ui->actionReset, SIGNAL(triggered()), SLOT(onActionresetTriggered()));

    // Buttons connections
    connect(ui->addRoutePushButton, &QPushButton::clicked, [this]()
    {
        cmd.Receive(factory.createRoute(manager));
    });
    connect(ui->removeRoutePushButton, &QPushButton::clicked, [this]()
    {
        QItemSelectionModel *selection = ui->routeTableView->selectionModel();
        QModelIndexList rows = selection->selectedIndexes();
        if(rows.size())
        {
            int row = rows.front().row();
            int id = routes.data(routes.index(row, 0)).toInt();
            cmd.Receive(factory.removeRoute(manager, id));
        }
    });
    connect(ui->addPointPushButton, &QPushButton::clicked, [this]()
    {
        cmd.Receive(factory.createPoint(manager, QPointF(0, 0)));
    });
    connect(ui->removePointPushButton, &QPushButton::clicked, [this]()
    {
        QItemSelectionModel *selection = ui->pointTableView->selectionModel();
        QModelIndexList rows = selection->selectedIndexes();
        if(rows.size())
        {
            int row = rows.front().row();
            int id = points.data(points.index(row, 0)).toInt();
            cmd.Receive(factory.removePoint(manager, id));
        }
    });
}

void MainWindow::onActionundoTriggered()
{
    cmd.undo();
}

void MainWindow::onActionredoTriggered()
{
    cmd.redo();
}

void MainWindow::onActionresetTriggered()
{
    if(QMessageBox::warning(nullptr, "Reset operation", "This operation is undoable!") == QMessageBox::Ok)
        cmd.Receive(factory.reset(manager));
}

void MainWindow::setValidators()
{
    QDoubleValidator *longitudeVal = new QDoubleValidator(-180, 180, 5);
    QDoubleValidator *latitudeVal = new QDoubleValidator(-90, 90, 5);

    ui->longitudeLine->setValidator(longitudeVal);
    ui->latitudeLine->setValidator(latitudeVal);
}
