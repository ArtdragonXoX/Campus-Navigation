#pragma once

//算法类
//使用说明： Dijistra法 路径ID的QList = 类变量名.ReturnData(终点,类变量名.Method(起点, 类变量名.AddMiddlPoint(类变量名.DataPutIn(传入的QList)))); 


#include <QPoint>
#include <qmath.h>

#include "Definition.h"
#include "GlobalVariable.h"

#include <string.h>
#include <cfloat>
#include <stack>
#include <utility>
#include <queue>

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

typedef struct Apoint{
	WayPoint point;
	uint16_t fatherpoint;
	uint16_t road;
	double alreadCost;
    double moveCost;

	bool operator > (const Apoint& other) const
	{
		if (moveCost+alreadCost > other.moveCost + other.alreadCost)
			return true;
		else
			return false;
	}
	bool operator < (const Apoint& other) const
	{
		if (moveCost + alreadCost < other.moveCost + other.alreadCost)
			return true;
		else
			return false;
	}
}Apoint;

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

	static PointList DataPutIn(QList<uint16_t>(&WayPointList));//数据录入
	static PointList AddMiddlPoint(PointList pointList);//补充未给予途径点,制作所需数据
	static AnswerList Method(uint16_t startPointID, PointList pointList);//Dijkatra算法实现
	static AnswerList Method(uint16_t startPoint, uint16_t endPoint, PointList pointList);//A*算法实现
	static QList<pair<uint16_t, uint16_t>> ReturnData(uint16_t endPointID, AnswerList answerList);//输出结果数据
	static QList<pair<uint16_t, uint16_t>> ReturnData(AnswerList answerList);//输出A*结果数据
	static uint16_t DeepSearch(uint16_t startPointID, uint16_t endPointID,uint16_t lastPointID, double lastcost, PointList& pointList);
	static pair<double, uint16_t> JudgeSameRoad(uint16_t point1, uint16_t point2);
	static bool CheckSame(uint16_t point,PointList (&pointList));
	static double CalcuCost(uint16_t startPointID, uint16_t endPointID);
	static QList<pair<uint16_t, uint16_t>> Traceback(Apoint endPoint, QList<Apoint> closeList,uint16_t startPointID);
	static void MakeList(PointList& pointList);
};
