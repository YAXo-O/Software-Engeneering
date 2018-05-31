#include <QVBoxLayout>
#include <QPushButton>
#include "plugintableview.h"

PluginTableView::PluginTableView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *_layout = new QVBoxLayout;
    _layout->addWidget(&table);
    setLayout(_layout);

    setWindowIconText("Plugins table");
}

void PluginTableView::show(QHash<QString, loaderData> *pluginTable)
{
    table.clear();
    QList<QString> keys = pluginTable->keys();
    table.setRowCount(keys.count());
    table.setColumnCount(2);
    int i = 0;
    for(auto key: keys)
    {
        QTableWidgetItem *item = new QTableWidgetItem(key);
        table.setItem(i, 0, item);

        QPushButton *btn = new QPushButton();
        btn->setText("Run");

        table.setCellWidget(i++, 1, btn);
        connect(btn, &QPushButton::clicked, [this, pluginTable, key]()->void
        {
            emit sendVisitor(pluginTable->operator[](key).visitor);
        });
    }

    QWidget::show();
}
