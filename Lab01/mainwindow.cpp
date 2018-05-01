#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->routeTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    setValidators();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QTableView *MainWindow::getRoutesView() const
{
    return ui->routeTableView;
}

QTableView *MainWindow::getPointsView() const
{
    return ui->pointTableView;
}

void MainWindow::currentRoute(const QString &name)
{
    ui->routeNameLine->setText(name);
}

void MainWindow::currentPoint(double longitude, double latitude, double height)
{
    ui->longitudeLine->setText(QString::number(longitude));
    ui->latitudeLine->setText(QString::number(latitude));
    ui->heightLine->setText(QString::number(height));
}

void MainWindow::receiveError(const QString &title, const QString &message, errorLevel level)
{
    switch(level)
    {
    case EL_INFO:
        QMessageBox::information(this, title, message);
        break;

    case EL_WARNING:
        QMessageBox::warning(this, title, message);
        break;

    case EL_CRITICAL:
        QMessageBox::critical(this, title, message);
        break;

    default:
        QMessageBox::about(this, title, message);
        break;
    }
}


void MainWindow::setConnections()
{
    // Table selection
    connect(ui->routeTableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            [this](QModelIndex selected, QModelIndex)
    {
        emit routeTableSelectionChanged(selected);
    });
    connect(ui->pointTableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            [this](QModelIndex selected, QModelIndex)
    {
        emit pointsTableSelectionChanged(selected);
    });

    // Data user changed
    connect(ui->routeNameLine, &QLineEdit::returnPressed, [this]()
    {
        emit renameRoute(ui->routeTableView->selectionModel(), ui->routeNameLine->text());
    });
    connect(ui->longitudeLine, &QLineEdit::returnPressed, [this]()
    {
        emit changeLongitude(ui->pointTableView->selectionModel(), ui->longitudeLine->text().toDouble());
    });
    connect(ui->latitudeLine, &QLineEdit::returnPressed, [this]()
    {
        emit changeLatitude(ui->pointTableView->selectionModel(), ui->latitudeLine->text().toDouble());
    });
    connect(ui->heightLine, &QLineEdit::returnPressed, [this]()
    {
        emit changeHeight(ui->pointTableView->selectionModel(), ui->heightLine->text().toDouble());
    });

    // Actions connections
    connect(ui->actionLoad, SIGNAL(triggered()), SLOT(onActionloadTriggered()));
    connect(ui->actionUndo, SIGNAL(triggered()), SIGNAL(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), SIGNAL(redo()));
    connect(ui->actionReset, SIGNAL(triggered()), SLOT(onActionresetTriggered()));
    connect(ui->actionCreateRoute, SIGNAL(triggered()), SLOT(onActioncreaterouteTriggered()));
    connect(ui->actionUpdatePolyline, SIGNAL(triggered()), SLOT(onActionupdatepolylineTriggered()));

    // Buttons connections
    connect(ui->addRoutePushButton, SIGNAL(clicked()), SIGNAL(createRoute()));
    connect(ui->removeRoutePushButton, &QPushButton::clicked, [this]()
    {
        emit removeRoute(ui->routeTableView->selectionModel());
    });
    connect(ui->addPointPushButton, SIGNAL(clicked()), SIGNAL(createPoint()));
    connect(ui->removePointPushButton, &QPushButton::clicked, [this]()
    {
        emit removePoint(ui->pointTableView->selectionModel());
    });
}

void MainWindow::setValidators()
{
    QDoubleValidator *longitudeVal = new QDoubleValidator(-180, 180, 5);
    QDoubleValidator *latitudeVal = new QDoubleValidator(-90, 90, 5);
    QDoubleValidator *heightVal = new QDoubleValidator();

    ui->longitudeLine->setValidator(longitudeVal);
    ui->latitudeLine->setValidator(latitudeVal);
    ui->heightLine->setValidator(heightVal);
}

void MainWindow::onActionloadTriggered()
{
    QStringList filename = QFileDialog::getOpenFileNames(nullptr, "GPX File", QString(), "*.gpx");
    if(filename.isEmpty())
        return;

    for(auto i : filename)
        emit loadFile(i);
}

void MainWindow::onActionresetTriggered()
{
    if(QMessageBox::warning(nullptr, "Reset operation", "This operation is not undoable!") == QMessageBox::Ok)
        emit doReset();
}

void MainWindow::onActioncreaterouteTriggered()
{
    emit readPolyline(QFileDialog::getOpenFileName(this, "Polyline file", QString(), "*.txt"));
}

void MainWindow::onActionupdatepolylineTriggered()
{
    emit writePolyline(QFileDialog::getSaveFileName(this, "Polyline file", QString(), "*.txt"));
}
