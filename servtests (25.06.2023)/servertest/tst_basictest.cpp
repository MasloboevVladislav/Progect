#include <QtTest>
#include <../../server/functions.cpp>

// add necessary includes here

class basictest : public QObject
{
    Q_OBJECT

public:
    basictest();
    ~basictest();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();

};

basictest::basictest()
{

}

basictest::~basictest()
{

}

void basictest::test_case1()
{
    QVERIFY(CheckTask1Answer("4:(1;3),(0;1),(0;3),(1;2):0130")== true);
    QVERIFY(CheckTask1Answer("4:(0;2),(1;3),(0;1),(0;3),(2;3):4324")== false);
    QVERIFY(CheckTask1Answer("5:(0;2),(1;3),(0;1),(0;4),(1;2):0210")== true);
}

void basictest::test_case2()
{
    QVERIFY(CheckTask2Answer("4:(0;2),(1;3),(1;2),(2;3):2132")==true);
    QVERIFY(CheckTask2Answer("4:(0;2),(1;3),(0;3),(1;2),(2;3):12343")==false);
    QVERIFY(CheckTask2Answer("4:(0;2),(0;3),(1;2),(2;3):0230")==true);
}

void basictest::test_case3()
{
    QVERIFY(CheckTask3Answer("5:(1;3),(0;3),(0;4),(1;4),(2;3):12")==false);
    QVERIFY(CheckTask3Answer("4:(0;1),(0;3),(1;2),(2;3):02")==true);
    QVERIFY(CheckTask3Answer("5:(1;3),(0;1),(0;4),(2;4),(1;2),(3;4):14")==false);
}

void basictest::test_case4()
{
    QVERIFY(authorization("admin", "admin")=="true");
    QVERIFY(authorization("admin", "adminq")=="false");
    QVERIFY(authorization("adminq", "admin")=="false");

}

QTEST_APPLESS_MAIN(basictest)

#include "tst_basictest.moc"
