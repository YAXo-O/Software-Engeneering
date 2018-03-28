#ifndef POINTSSAVER_H
#define POINTSSAVER_H

#include <QPointF>
#include "../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.h"

template<typename T>
class QVector;

class PointsSaver : public gpolyline::DecoderFunctor
{
public:
    PointsSaver(QVector<QPointF> *holder);
    ~PointsSaver() override {}

    void operator()(double longitude, double latitude) override;

private:
    QVector<QPointF> *points;
};

#endif // POINTSSAVER_H
