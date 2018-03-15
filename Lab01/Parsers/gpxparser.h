#ifndef GPXPARSER_H
#define GPXPARSER_H

#include <QString>
#include <QVector>
#include "dbmanager.h"

class GPXParser
{
public:
    GPXParser() = default;

    void parse(const QString &filename, DBManager &manager)
        throw(std::invalid_argument, std::ios_base::failure);
};

#endif // GPXPARSER_H
