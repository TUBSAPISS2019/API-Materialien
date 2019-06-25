#include "ledcontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDControl w;
    w.show();

    return a.exec();
}
