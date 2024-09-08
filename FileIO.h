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
	static void WriteMapData();

	//读取地图数据
	//static void ReadMapData();
	static void ReadMapData(const char* filename_point, const char* filename_road);

private:
	//解析数据
	static void ParseData(QJsonDocument Jdoc);

	//写入路径点数据
	//static void ReadWayPointData();
	static void WriteWayPointData(QMap<uint16_t, WayPoint> pointMap);

	//写入路线数据
	//static void ReadRoadData();
	static void WriteRoadData(QMap <uint16_t, Road> roadMap);

	//读取json文件
	static QJsonDocument ReadJsonFile(const char* filename);

	//解析路点数据
	static void ParseWayPoint(QJsonDocument point);

	//解析路线数据
	static void ParseRoadData(QJsonDocument road);
};
