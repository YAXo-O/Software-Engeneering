#include <QVector>
#include "pointssaver.h"

PointsSaver::PointsSaver(QVector<QGeoCoordinate> *holder): gpolyline::DecoderFunctor(), coordinates(holder)
{
}

void PointsSaver::operator()(double longitude, double latitude)
{
    if(!coordinates)
        return;

    if(coordinates->size())
        coordinates->append(QGeoCoordinate(coordinates->back().longitude() + longitude, coordinates->back().latitude() + latitude));
    else
        coordinates->append(QGeoCoordinate(longitude, latitude));
}
