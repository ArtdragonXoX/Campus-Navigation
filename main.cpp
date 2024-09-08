#include "MianWindow.h"
#include <QtWidgets/QApplication>
#include <FileIO.h>

int main(int argc, char* argv[])
{
    FileIO io;
    char add1[] = "d://Project2//test1.json";
    char add2[] = "d://Project2//test2.json";
    io.ReadMapData(add1, add2);
    QApplication a(argc, argv);
    MianWindow w;
    w.show();
    return a.exec();
}
