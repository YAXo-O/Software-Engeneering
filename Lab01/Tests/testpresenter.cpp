#include "testpresenter.h"

TestPresenter::TestPresenter(QObject *parent): Presenter(parent)
{
}

void TestPresenter::createRoute()
{
    qDebug() << "Create route: success";
}

void TestPresenter::createPoint()
{
    qDebug() << "Create point: success";
}

void TestPresenter::removePoint(QItemSelectionModel *selection)
{
    if(selection && selection->selectedIndexes().count())
        qDebug() << "Remove point: success";
    else
        qDebug() << "Remove point: no selection";
}

void TestPresenter::drawHeightMap(QItemSelectionModel *selection)
{
    if(selection && selection->selectedIndexes().count())
        qDebug() << "drawHeightMap: success";
    else
        qDebug() << "drawHeightMap: no selectoin";
}
