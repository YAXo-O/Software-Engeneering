#include <QDir>
#include <QThread>
#include <QApplication>
#include <QPluginLoader>
#include <QDateTime>

#include "model.h"
#include "pluginmanager.h"
#include "Visitors/abstractvisitor.h"

#include <QDebug>

PluginManager::PluginManager(Model *_model, unsigned long _sleepTime, QObject *parent) : QObject(parent),
    model(_model),sleepTime(_sleepTime)
{

}

void PluginManager::checkLoop()
{
   QDir dir = QApplication::applicationDirPath();
   QString lower = dir.dirName().toLower();
   if(lower == "debug" || lower == "release")
   {
       dir.cdUp();
       dir.cdUp();
   }
   dir.cd("plugins");
   dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

   QStringList filter = QStringList() << "*.dll";

   while(1)
   {
       dir.refresh();
       QFileInfoList fileinfo = dir.entryInfoList(filter);

       for(auto file: fileinfo)
       {
           if(needsLoading(file, dir))
           {
               QPluginLoader loader(dir.absoluteFilePath(file.fileName()));
               QObject *plugin = loader.instance();
               if(plugin)
               {
                   AbstractVisitor *visitor = qobject_cast<AbstractVisitor *>(plugin);
                   if(visitor)
                       pluginTable[file.fileName()] = {.visitor = visitor, .fileInfo = file};
               }
           }
       }

       QThread::sleep(sleepTime);
   }
}

bool PluginManager::needsLoading(const QFileInfo file, const QDir &dir)
{
    if(pluginTable.contains(file.fileName()))
    {
        QFileInfo finfo = pluginTable[file.fileName()].fileInfo;
        if(file.lastModified() > finfo.lastModified())
        {
            QPluginLoader unloader(dir.absoluteFilePath(finfo.fileName()));
            unloader.unload();

            return true;
        }

        return false;
    }

    return true;
}
