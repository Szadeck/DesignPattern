#include <QCoreApplication>

#include "testmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestManager tm;
    tm.launchAllTest();

    return a.exec();
}
