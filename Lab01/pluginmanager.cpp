#include <QDir>
#include <QThread>

#include "pluginmanager.h"

#include <QDebug>

PluginManager::PluginManager(unsigned long _sleepTime, QObject *parent) : QObject(parent), sleepTime(_sleepTime)
{

}

void PluginManager::checkLoop()
{
   QDir dir;

   while(1)
   {
       dir = QDir::currentPath();
       qDebug() << dir.absolutePath();

       QThread::sleep(sleepTime);
   }
}
