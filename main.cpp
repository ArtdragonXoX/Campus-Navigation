#include "MianWindow.h"
#include <QtWidgets/QApplication>
#include <FileIO.h>
#include "Definition.h"
using namespace std;

int main(int argc, char* argv[])
{
    FileIO io;

    QMap<uint16_t, WayPoint> pointMap;
    WayPoint wayPoint1 = { 1, QString::fromLocal8Bit("Àﬁ…·"), {10.0, 20.0}, Buildings, QList<uint16_t>({101, 102}) };
    WayPoint wayPoint2 = { 2, QString::fromLocal8Bit(" ≥Ã√"), {30.0, 40.0}, RoadNode,  QList<uint16_t>({201, 202}) };
    WayPoint wayPoint3 = { 3, QString::fromLocal8Bit(" µ—È¬•"), {50.0, 60.0}, Buildings, QList<uint16_t>({301, 123}) };
    
    pointMap.insert(1, wayPoint1);
    pointMap.insert(2, wayPoint2); 
    pointMap.insert(3, wayPoint3);

    QMap<uint16_t, Road> roadMap;
    roadMap[1] = { 1, 2, 3 };
    roadMap[2] = { 4, 5, 6 };
    roadMap[3] = { 7, 8, 9 };
    
    io.WriteMapData(pointMap,roadMap);

    
    //char add1[] = "d://Project2//test1.json";
    //char add2[] = "d://Project2//test2.json";
    //io.ReadMapData(add1,add2);
    QApplication a(argc, argv);
    MianWindow w;
    w.show();
    return a.exec();
}
