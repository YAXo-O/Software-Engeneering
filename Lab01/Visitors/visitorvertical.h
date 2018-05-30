#ifndef VISITORVERTICAL_H
#define VISITORVERTICAL_H

#include "abstractvisitor.h"

class VisitorVertical : public QObject, AbstractVisitor
{
    Q_OBJECT
    Q_INTERFACES(AbstractVisitor)
    //Q_PLUGIN_METADATA(IID "YAX.PPO.AbstractVisitor.Vertical" FILE "visitorvertical.json")

public:
    VisitorVertical() = default;
    ~VisitorVertical() override {}

    void operator()(Model &m) override;
};

#endif // VISITORVERTICAL_H
