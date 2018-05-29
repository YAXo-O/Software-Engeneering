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
    int routeId = -1;
    while(!reader.atEnd() && !reader.hasError())
    {
        auto token = reader.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "trk")
                routeId = manager.addRoute(filename.split("/").last().split(".").first());

            if(reader.name() == "trkpt")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                bool bOk = false;

                double longitude = attrib.value("lon").toDouble(&bOk);
                if(!bOk)
                {
                    if(routeId != -1)
                        manager.removeRoute(routeId);
                    manager.enableNotifications();
                    throw std::invalid_argument("Longitude is abscent");
                }
                if(longitude > 180 || longitude < -180)
                {
                    if(routeId != -1)
                        manager.removeRoute(routeId);
                    manager.enableNotifications();
                    throw std::invalid_argument("Longitude is out of range!");
                }
                double latitude = attrib.value("lat").toDouble(&bOk);
                if(!bOk)
                {
                    if(routeId != -1)
                        manager.removeRoute(routeId);
                    manager.enableNotifications();
                    throw std::invalid_argument("Latitude is abscent");
                }
                if(latitude > 90 || latitude < -90)
                {
                    if(routeId != -1)
                        manager.removeRoute(routeId);
                    manager.enableNotifications();
                    throw std::invalid_argument("Latitude is out of range!");
                }

                double height = 0;
                while(!reader.atEnd() && !reader.hasError() && reader.tokenType() != QXmlStreamReader::EndElement)
                {
                    reader.readNext();

                    if(reader.name() == "ele")
                    {
                        height = reader.readElementText().toDouble(&bOk);
                        if(!bOk)
                        {
                            if(routeId != -1)
                                manager.removeRoute(routeId);
                            manager.enableNotifications();
                            throw std::invalid_argument("Height is corrupted!");
                        }
                    }
                }

                manager.addPoint(QGeoCoordinate(latitude, longitude, height));
            }
        }
    }

    manager.selectRoute(routeId);
    manager.enableNotifications();
    manager.refresh();
}
