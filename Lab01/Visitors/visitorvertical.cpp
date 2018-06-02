#include <QTableWidget>
#include <QGeoCoordinate>
#include <QMessageBox>

#include "../dbmanager.h"
#include "visitorvertical.h"

const int minimalPointCount = 10;
const double factor = 180.f/M_PI;

void VisitorVertical::operator()(DBManager &m)
{
    QVector<QGeoCoordinate> *coords = m.getPoints(m.getCurrentRoute());
    if(coords->count() < minimalPointCount)
    {
        QMessageBox::information(nullptr, "Downhill signs statistics", "Too few points in route!");

        return;
    }

    QGeoCoordinate start = coords->at(0);
    QGeoCoordinate prev = start;
    QGeoCoordinate cur = coords->at(1);
    double dif = cur.altitude() - prev.altitude();
    double len = prev.distanceTo(cur);

    unsigned int type[5] = {0, 0, 0, 0, 0};

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
            double tg = tan(angle);

            putType(type, tg, len);

            len = 0;
            dif = cur_dif;
            start = cur;
        }
    }

    QTableWidget *table = new QTableWidget(5, 2);
    QString titles[5] = {".4", ".5", ".6", ".7", ".8"};

    for(int i = 0; i < 5; i++)
    {
        QTableWidgetItem *title = new QTableWidgetItem(titles[i]);
        QTableWidgetItem *value = new QTableWidgetItem(QString::number(type[i]));

        table->setItem(i, 0, title);
        table->setItem(i, 1, value);
    }

    table->show();
}

void VisitorVertical::putType(unsigned int type[], double tg, double len)
{
    if(tg >= .8 && len >= 270)
        type[4]++;
    else if(tg >= .7 && len >= 300)
        type[3]++;
    else if(tg >= .6 && len >= 350)
        type[2]++;
    else if(tg >= .5 && len >= 450)
        type[1]++;
    if(tg >= .4 && len >= 600)
        type[0]++;
}
