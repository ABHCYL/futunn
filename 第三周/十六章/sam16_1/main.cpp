#include "widget.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qt;
    a.installTranslator(&qt);
    qt.load("D:/learn/sam16_1/cn.qm");
    Widget w;
    w.show();
    return a.exec();
}
