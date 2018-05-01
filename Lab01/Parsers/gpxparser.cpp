#include <QFile>
#include <QGeoCoordinate>
#include <QXMLStreamReader>

#include "gpxparser.h"

void GPXParser::parse(const QString &filename, DBManager &manager)
    throw(std::invalid_argument, std::ios_base::failure)
{

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        throw std::ios_base::failure("Can't open file!");

    QXmlStreamReader reader(file.readAll());

    manager.disableNotifications();
    while(!reader.atEnd() && !reader.hasError())
    {
        auto token = reader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "trk")
                manager.addRoute(filename.split("/").last().split(".").first());

            if(reader.name() == "trkpt")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                bool bOk = false;

                double longitude = attrib.value("lon").toDouble(&bOk);
                if(!bOk)
                {
                    manager.enableNotifications();
                    throw std::invalid_argument("Longitude is abscent");
                }
                if(longitude > 180 || longitude < -180)
                {
                    manager.enableNotifications();
                    throw std::invalid_argument("Longitude is out of range!");
                }
                double latitude = attrib.value("lat").toDouble(&bOk);
                if(!bOk)
                {
                    manager.enableNotifications();
                    throw std::invalid_argument("Latitude is abscent");
                }
                if(latitude > 90 || latitude < -90)
                {
                    manager.enableNotifications();
                    throw std::invalid_argument("Latitude is out of range!");
                }

                manager.addPoint(QGeoCoordinate(longitude, latitude));
            }
        }
    }

    manager.selectRoute(-1);
    manager.enableNotifications();
    manager.refresh();
}
