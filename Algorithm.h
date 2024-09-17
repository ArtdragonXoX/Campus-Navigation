#pragma once

//�㷨��
//ʹ��˵���� Dijistra�� ·��ID��QList = �������.ReturnData(�յ�,�������.Method(���, �������.AddMiddlPoint(�������.DataPutIn(�����QList)))); 


#include <QPoint>
#include <qmath.h>

#include "Definition.h"
#include "GlobalVariable.h"

#include <string.h>
#include <cfloat>
#include <stack>
#include <utility>

using namespace GlobalVariable;
using namespace std;

#define INF DBL_MAX 

typedef struct PointList {
	QList<uint16_t> WayPointList;
	QList<QList<double>> AdjTable;
	QList<QList<uint16_t>> RoadTable;
	QList<uint16_t> CheckList;
	uint16_t PointNum;
}PointList;

typedef struct AnswerList {
	QList<uint16_t> WayPointList;
	QList<double> dist;
	QList<uint16_t> p;
	QList<uint16_t> p_road;
	uint16_t startPointID;
}AnswerList;

class Algorithm
{
public:

	static PointList DataPutIn(QList<uint16_t>(&WayPointList));//����¼��
	static PointList AddMiddlPoint(PointList pointList);//����δ����;����,������������
	static void Method();
	static AnswerList Method(uint16_t startPointID, PointList pointList);//Dijkatra�㷨ʵ��
	//static void Method(int y);//A*�㷨ʵ��
	static QList<pair<uint16_t, uint16_t>> ReturnData(uint16_t endPointID, AnswerList answerList);//����������
	static uint16_t DeepSearch(uint16_t startPointID, uint16_t endPointID, uint16_t lastPointID, PointList& pointList);
	static pair<double, uint16_t> JudgeSameRoad(uint16_t point1, uint16_t point2);
	static bool CheckSame(uint16_t point,PointList (&pointList));
};