#include "qmybattery.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QmyBattery w;
    w.show();
    return a.exec();
}
