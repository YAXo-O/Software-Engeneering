#include <QTableWidget>
#include <QVector3D>
#include <QMessageBox>

#include "visitorturns.h"
#include "../dbmanager.h"

#include <QDebug>

const int turnLen = 15; // distance(meters) between Points
const double R = 6371; // Earth Radius
const double factor = 180.f/M_PI;
const int minimalPointCount = 10;

void VisitorTurns::operator()(DBManager &m)
{
    QVector<QGeoCoordinate> *coords = m.getPoints(m.getCurrentRoute());
    if(coords->count() < minimalPointCount)
    {
        QMessageBox::information(nullptr, "Turns count", "Too few points in route!");

        return;
    }

    QGeoCoordinate prev = coords->at(0);
    QVector3D prevDir(getPoint(coords->at(2)) - getPoint(prev));

    unsigned int values[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    int limit = coords->count() - 1;
    for(int i = 1; i < limit; i++)
    {
        QGeoCoordinate cur = coords->at(i);
        if(prev.distanceTo(cur) >= turnLen)
        {
            QVector3D curDir(getPoint(coords->at(i + 1)) - getPoint(coords->at(i - 1)));
            float angle = factor*fabs(acos(QVector3D::dotProduct(prevDir, curDir)/(prevDir.length()*curDir.length())));
            putValue(values, angle);
        }
    }

    QTableWidget *tableWidget = new QTableWidget(8, 2);
    for(int i = 0; i < 8; i++)
    {
        QTableWidgetItem *cat = new QTableWidgetItem(QString("Category ") + QString::number(i));
        QTableWidgetItem *count = new QTableWidgetItem(QString::number(values[i]));
        tableWidget->setItem(i, 0, cat);
        tableWidget->setItem(i, 1, count);
    }
    tableWidget->show();
}

QVector3D VisitorTurns::getPoint(const QGeoCoordinate &c)
{
    double h = R + c.altitude();
    double longitude = c.longitude();
    double latitude = c.latitude();
    double coslat = cos(latitude);

    return QVector3D(h*coslat*cos(longitude), h*coslat*sin(longitude), h*sin(latitude));
}

void VisitorTurns::putValue(unsigned int values[], double value)
{
    if(value < 1)
        return;
    else if(value < 6)
        values[0]++;
    else if(value <= 11)
        values[1]++;
    else if(value <= 33.5)
        values[2]++;
    else if(value <= 56)
        values[3]++;
    else if(value <= 78.5)
        values[4]++;
    else if(value <= 90)
        values[5]++;
    else if(value <=135)
        values[6]++;
    else
        values[7]++;
}
