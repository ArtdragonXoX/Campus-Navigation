#pragma once

//文件读取输出类

#include <iostream>
#include <fstream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>

#include "Definition.h"
#include "GlobalVariable.h"

class FileIO
{
public:
	//读取地图数据
	static void ReadMapData();
	static void ReadMapData(const char* filename);

private:
	//读取路点数据
	static void ReadWayPointData();
	static void ReadWayPointData(const char* filename);

	//读取路线数据
	static void ReadRoadData();
	static void ReadRoadData(const char* filename);

	//读取json文件
	static QJsonDocument ReadJsonFile(const char* filename);

	//解析路点数据
	static void ParseWayPoint(QJsonDocument jsonDocument);

	//解析路线数据
	static void ParseRoadData(QJsonDocument jsonDocument);
};
