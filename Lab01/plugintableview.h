#ifndef PLUGINTABLEVIEW_H
#define PLUGINTABLEVIEW_H

#include <QWidget>
#include <QTableWidget>
#include "pluginmanager.h"

class PluginTableView : public QWidget
{
    Q_OBJECT
public:
    explicit PluginTableView(QWidget *parent = nullptr);

    void show(QHash<QString, loaderData> *pluginTable);

private:
    QTableWidget table;

signals:
    void sendVisitor(AbstractVisitor *visitor);

};

#endif // PLUGINTABLEVIEW_H
