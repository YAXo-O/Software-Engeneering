#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QFileInfo>
#include <QHash>

class Model;
class AbstractVisitor;

struct loaderData
{
    AbstractVisitor *visitor;
    QFileInfo fileInfo;
};

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

    QHash<QString, loaderData> pluginTable;

    bool needsLoading(const QFileInfo file, const QDir &dir);
};

#endif // PLUGINMANAGER_H
