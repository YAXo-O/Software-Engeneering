#ifndef IMPORTPOLYLINE_H
#define IMPORTPOLYLINE_H

#include <QGeoCoordinate>
#include <QString>

#include "./command.h"

template<typename T>
class QVector;
class QPointF;
class DBManager;

class ImportPolyline : public Command
{
public:
    ImportPolyline(const QString &name, QVector<QGeoCoordinate> &coordinates, DBManager &manager);
    ~ImportPolyline() override {}

    void exec() override;
    void reject() override;

    bool isUndoable() override;

private:
    const QString &name;
    QVector<QGeoCoordinate> &coordinates;
    DBManager &manager;
};

#endif // IMPORTPOLYLINE_H
