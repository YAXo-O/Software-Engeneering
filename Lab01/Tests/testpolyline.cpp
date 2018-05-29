#include <QTest>
#include <QString>

#include "../../GooglePolylineCoder/GooglePolylineCoder/googlepolylinecoder.h"

#include "testpolyline.h"

TestPolyline::TestPolyline(QObject *parent) : QObject(parent)
{
}

void TestPolyline::testZero()
{
    QVERIFY(gpolyline::encode(0, 0) == "??");
    QVERIFY(gpolyline::encode(0.000001, 0.000001) == "??");
}

void TestPolyline::testMax()
{
    QVERIFY(gpolyline::encode(-180, -90) == "~bidP~fsia@");
    QVERIFY(gpolyline::encode(180, 90) == "_cidP_gsia@");
}

void TestPolyline::testRound()
{
    QVERIFY(gpolyline::encode(0.000001, 0.000006) == "A?");
    QVERIFY(gpolyline::encode(-0.000001, -0.000006) == "@?");
}

void TestPolyline::decode()
{
    gpolyline::decode("??", [](double longitude, double latitude)
    {
       QVERIFY(longitude == 0 && latitude == 0);
    });
    gpolyline::decode("~bidP~fsia@", [](double longitude, double latitude)
    {
       QVERIFY(longitude == -180 && latitude == -90);
    });
    gpolyline::decode("_cidP_gsia@", [](double longitude, double latitude)
    {
       QVERIFY(longitude == 180 && latitude == 90);
    });
}

//QTEST_MAIN(TestPolyline)
