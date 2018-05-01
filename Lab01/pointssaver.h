#ifndef POINTSSAVER_H
#define POINTSSAVER_H

#include <QGeoCoordinate>
#include "../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.h"

template<typename T>
class QVector;

class PointsSaver : public gpolyline::DecoderFunctor
{
public:
    PointsSaver(QVector<QGeoCoordinate> *holder);
    ~PointsSaver() override {}

    void operator()(double longitude, double latitude) override;

private:
    QVector<QGeoCoordinate> *coordinates;
};

#endif // POINTSSAVER_H
