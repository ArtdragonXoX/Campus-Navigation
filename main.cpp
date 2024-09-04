#include "MianWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MianWindow w;
    w.show();
    return a.exec();
}
