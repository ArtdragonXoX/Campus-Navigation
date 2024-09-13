#pragma once

//文件读取输出类
#include <QFile>
#include <iostream>
#include <fstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QString>
#include <QDebug>

#include "Definition.h"
#include "GlobalVariable.h"


class FileIO
{
public:

	//写入地图数据
	//static void WriteMapData();
	static void WriteMapData(QMap <uint16_t, WayPoint> pointMap, QMap <uint16_t, Road> roadMap);

	//读取地图数据
	//static void ReadMapData();
	static void ReadMapData(const char* filename_point, const char* filename_road);

private:

	//解析路径点数据
	static void ParseWayPointData(QJsonDocument Jdoc);

	//解析路线数据
	static void ParseWayRoadData(QJsonDocument Jdoc);

	//路径点结构转换json对象
	static QJsonObject QMap_WayPointToJson(QMap<uint16_t, WayPoint>& pointMap);

	//道路结构转换json对象
	static QJsonObject QMap_RoadToJson(QMap<uint16_t, Road>& pointMap);

	//对象写入文件
	void static WriteToJsonFile(QJsonObject& jsonObject, const QString& fileName);

	//struct WayPoint->Object
	static QJsonObject WayPointToObject(WayPoint& waypoint);

	//struct Road->Object
	static QJsonObject RoadToObject(Road& road);

	//读取json文件
	static QJsonDocument ReadJsonFile(const char* filename);

	//解析路点
	static void ParseWayPoint(QJsonDocument point);

	//解析路线
	static void ParseRoad(QJsonDocument road);
};
