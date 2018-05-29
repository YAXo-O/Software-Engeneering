#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class PluginManager : public QObject
{
    Q_OBJECT
public:
    explicit PluginManager(unsigned long sleepTime = 3, QObject *parent = nullptr);

public slots:
    void checkLoop();

private:
    unsigned long sleepTime;
};

#endif // PLUGINMANAGER_H
