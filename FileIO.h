#pragma once

//�ļ���ȡ�����
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

	//д���ͼ����
	//static void WriteMapData();
	static void WriteMapData(QMap <uint16_t, WayPoint> pointMap, QMap <uint16_t, Road> roadMap);

	//��ȡ��ͼ����
	//static void ReadMapData();
	static void ReadMapData(const char* filename_point, const char* filename_road);

private:

	//����·��������
	static void ParseWayPointData(QJsonDocument Jdoc);

	//����·������
	static void ParseWayRoadData(QJsonDocument Jdoc);

	//·����ṹת��json����
	static QJsonObject QMap_WayPointToJson(QMap<uint16_t, WayPoint>& pointMap);

	//��·�ṹת��json����
	static QJsonObject QMap_RoadToJson(QMap<uint16_t, Road>& pointMap);

	//����д���ļ�
	void static WriteToJsonFile(QJsonObject& jsonObject, const QString& fileName);

	//struct WayPoint->Object
	static QJsonObject WayPointToObject(WayPoint& waypoint);

	//struct Road->Object
	static QJsonObject RoadToObject(Road& road);

	//��ȡjson�ļ�
	static QJsonDocument ReadJsonFile(const char* filename);

	//����·��
	static void ParseWayPoint(QJsonDocument point);

	//����·��
	static void ParseRoad(QJsonDocument road);
};
