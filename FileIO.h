#pragma once

//�ļ���ȡ�����

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
	//��ȡ��ͼ����
	static void ReadMapData();
	static void ReadMapData(const char* filename);

private:
	//��ȡ·������
	static void ReadWayPointData();
	static void ReadWayPointData(const char* filename);

	//��ȡ·������
	static void ReadRoadData();
	static void ReadRoadData(const char* filename);

	//��ȡjson�ļ�
	static QJsonDocument ReadJsonFile(const char* filename);

	//����·������
	static void ParseWayPoint(QJsonDocument jsonDocument);

	//����·������
	static void ParseRoadData(QJsonDocument jsonDocument);
};
