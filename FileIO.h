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
	static void WriteMapData();

	//��ȡ��ͼ����
	//static void ReadMapData();
	static void ReadMapData(const char* filename_point, const char* filename_road);

private:
	//��������
	static void ParseData(QJsonDocument Jdoc);

	//д��·��������
	//static void ReadWayPointData();
	static void WriteWayPointData(QMap<uint16_t, WayPoint> pointMap);

	//д��·������
	//static void ReadRoadData();
	static void WriteRoadData(QMap <uint16_t, Road> roadMap);

	//��ȡjson�ļ�
	static QJsonDocument ReadJsonFile(const char* filename);

	//����·������
	static void ParseWayPoint(QJsonDocument point);

	//����·������
	static void ParseRoadData(QJsonDocument road);
};
