#ifndef TESTPOLYLINE_H
#define TESTPOLYLINE_H

#include <QObject>

class TestPolyline : public QObject
{
    Q_OBJECT
public:
    explicit TestPolyline(QObject *parent = nullptr);

private slots:
    void testZero();
    void testMax();
    void testRound();
    void decode();
};

#endif // TESTPOLYLINE_H
