#include "stringlistmodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StringListModel w;
    w.show();
    return a.exec();
}
