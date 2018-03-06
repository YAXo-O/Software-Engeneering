#include <QFile>
#include <QXMLStreamReader>

#include "gpxparser.h"

void GPXParser::parse(const QString &filename, RoutesManager *manager)
    throw(std::invalid_argument, std::ios_base::failure)
{
    if(!manager)
        throw std::invalid_argument("Manager is not specified");

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        throw std::ios_base::failure("Can't open file!");

    QXmlStreamReader reader(file.readAll());

    while(!reader.atEnd() && !reader.hasError())
    {
        auto token = reader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "trk")
                manager->addRoute(filename.split("/").last().split(".").first());

            if(reader.name() == "trkpt")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                bool bOk = false;

                double longitude = attrib.value("lon").toDouble(&bOk);
                if(!bOk)
                    throw std::invalid_argument("Longitude is abscent");
                double latitude = attrib.value("lat").toDouble(&bOk);
                if(!bOk)
                    throw std::invalid_argument("Latitude is abscent");

                manager->addPoint(longitude, latitude);
            }
        }
    }
}
