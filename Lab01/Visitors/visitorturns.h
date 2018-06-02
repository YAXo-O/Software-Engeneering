#ifndef VISITORTURNS_H
#define VISITORTURNS_H

#include <QGeoCoordinate>

#include "abstractvisitor.h"

class VisitorTurns : public QObject, public AbstractVisitor
{
    Q_OBJECT
    Q_INTERFACES(AbstractVisitor)
    Q_PLUGIN_METADATA(IID "YAX.PPO.AbstractVisitor" FILE "visitorturns.json")

public:
    VisitorTurns() = default;
    ~VisitorTurns() override {}

    void operator()(DBManager &m) override;

private:
    QVector3D getPoint(const QGeoCoordinate &c);
    void putValue(unsigned int values[], double value);
};

#endif // VISITORTURNS_H
