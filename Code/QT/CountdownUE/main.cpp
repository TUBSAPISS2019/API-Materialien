#include <QCoreApplication>
#include "countdouwn.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Countdouwn countdown;

    return a.exec();
}
