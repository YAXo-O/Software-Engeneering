#include <QDoubleValidator>
#include <QIntValidator>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setValidators();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValidators()
{
    QDoubleValidator *val = new QDoubleValidator();
    val->setLocale(QLocale::English);

    ui->latitudeLineEdit->setValidator(val);
    ui->longitudeLineEdit->setValidator(val);
    ui->levelLineEdit->setValidator(new QIntValidator(1, 10));
}
