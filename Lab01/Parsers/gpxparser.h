#ifndef GPXPARSER_H
#define GPXPARSER_H

#include <QString>
#include "../routesmanager.h"

class GPXParser
{
public:
    GPXParser() = default;

    void parse(const QString &filename, RoutesManager *manager = nullptr)
        throw(std::invalid_argument, std::ios_base::failure);
};

#endif // GPXPARSER_H
