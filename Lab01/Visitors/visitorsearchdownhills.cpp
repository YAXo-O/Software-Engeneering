#include <QTableWidget>
#include <QMessageBox>

#include "visitorsearchdownhills.h"
#include "../dbmanager.h"

#include <QDebug>

const int minimalPointCount = 10;
const double factor = 180.f/M_PI;

void VisitorSearchDownhills::operator()(DBManager &m)
{
    QVector<QGeoCoordinate> *coords = m.getPoints(m.getCurrentRoute());
    if(coords->count() < minimalPointCount)
    {
        QMessageBox::information(nullptr, "Downhill statistics", "Too few points in route!");

        return;
    }

    QGeoCoordinate start = coords->at(0);
    QGeoCoordinate prev = start;
    QGeoCoordinate cur = coords->at(1);
    double dif = cur.altitude() - prev.altitude();
    double len = prev.distanceTo(cur);

    unsigned int typeAngle[5] = {0, 0, 0, 0, 0};
    unsigned int typeLen[3] = {0, 0, 0};

    int limit = coords->count();
    for(int i = 2; i < limit; i++)
    {
        prev = cur;
        cur = coords->at(i);
        len += prev.distanceTo(cur);

        double cur_dif = cur.altitude() - prev.altitude();
        if(dif*cur_dif < 0)
        {
            double heightDif = fabs(cur.altitude() - start.altitude());
            double hyp = start.distanceTo(cur);
            double angle = factor*fabs(asin(heightDif/hyp));

            putType(typeAngle, typeLen, angle, len);
            len = 0;
            dif = cur_dif;
            start = cur;
        }
    }

    QTableWidget *table = new QTableWidget(8, 2);

    QString titlesAngle[5] = {"Very abrupt", "Abrupt", "Medium abrupt", "Flat", "Very flat"};
    QString titlesLen[3] = {"Long", "Medium", "Short"};

    for(int i = 0; i < 5; i++)
    {
        QTableWidgetItem *cat = new QTableWidgetItem(titlesAngle[i]);
        QTableWidgetItem *val = new QTableWidgetItem(QString::number(typeAngle[i]));

        table->setItem(i, 0, cat);
        table->setItem(i, 1, val);
    }

    for(int i = 0; i < 3; i++)
    {
        QTableWidgetItem *cat = new QTableWidgetItem(titlesLen[i]);
        QTableWidgetItem *val = new QTableWidgetItem(QString::number(typeLen[i]));

        table->setItem(i + 5, 0, cat);
        table->setItem(i + 5, 1, val);
    }

    table->show();
}

void VisitorSearchDownhills::putType(unsigned int typeAngle[], unsigned int typeLen[], double angle, double len)
{
    if(angle >= 35)
        typeAngle[0]++;
    else if(angle >= 15)
        typeAngle[1]++;
    else if(angle >= 8)
        typeAngle[2]++;
    else if(angle >= 4)
        typeAngle[3]++;
    else if(angle >= 2)
        typeAngle[4]++;

    if(len > 500)
        typeLen[0]++;
    else if(len >50)
        typeLen[1]++;
    else
        typeLen[2]++;
}
