#ifndef TESTPRESENTER_H
#define TESTPRESENTER_H

#include <QObject>
#include "../presenter.h"

class TestPresenter : public Presenter
{
    Q_OBJECT
public:
    TestPresenter(QObject *parent = nullptr);

public slots:
    void createRoute();
    void createPoint();
    void removePoint(QItemSelectionModel *selection);
    void drawHeightMap(QItemSelectionModel *selection);
};

#endif // TESTPRESENTER_H
