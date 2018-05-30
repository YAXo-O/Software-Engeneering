#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class Model;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(Model *model, unsigned long sleepTime = 3, QObject *parent = nullptr);

public slots:
    void checkLoop();

private:
    Model *model;
    unsigned long sleepTime;
};

#endif // PLUGINMANAGER_H
