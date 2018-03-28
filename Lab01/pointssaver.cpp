#include <QVector>
#include "pointssaver.h"

PointsSaver::PointsSaver(QVector<QPointF> *holder): gpolyline::DecoderFunctor(), points(holder)
{
}

void PointsSaver::operator()(double longitude, double latitude)
{
    if(!points)
        return;

    if(points->size())
        points->append(QPointF(points->back().x() + longitude, points->back().y() + latitude));
    else
        points->append(QPointF(longitude, latitude));
}
