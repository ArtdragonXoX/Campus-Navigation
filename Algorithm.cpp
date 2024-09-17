#include "Algorithm.h"
#include <iostream>//
using namespace GlobalVariable;
PointList Algorithm::DataPutIn(QList<uint16_t> (&WayPointList)) {
	/* 
	* 录入V,登记第一个pointNum
	*/
	PointList pointList;
	pointList.WayPointList = WayPointList;
	pointList.PointNum = pointList.WayPointList.size();

	return pointList;
}

PointList Algorithm::AddMiddlPoint(PointList pointList) {
	/*
	* 采用深度搜索补充隐藏点,并制作邻接表
	*/
	QList<double> tem;//初始化邻接表
	QList<uint16_t> temp;
	for (int i = 0;i < pointList.PointNum;i++) {
		tem.push_back(INF);
		temp.push_back(UINT16_MAX);
	}	
	for (int i = 0;i < pointList.PointNum;i++) {
		pointList.AdjTable.push_back(tem);
		pointList.RoadTable.push_back(temp);
	}
		
	uint16_t searchNum = pointList.PointNum;
	for (uint16_t i = 0;i < searchNum;i++) {
		for (uint16_t j = i;j < searchNum;j++) {
			pair<double, uint16_t> judge = JudgeSameRoad(pointList.WayPointList[i], pointList.WayPointList[j]);
			if (judge.first==INF) {
				DeepSearch(pointList.WayPointList[i], pointList.WayPointList[j],0,pointList);
				pointList.CheckList.clear();
			}
			else {
				pointList.AdjTable[i][j] = judge.first;
				pointList.AdjTable[j][i] = judge.first;

				pointList.RoadTable[i][j] = judge.second;
				pointList.RoadTable[j][i] = judge.second;
			}
		}
	}
	return pointList;
}

pair<double,uint16_t> Algorithm::JudgeSameRoad(uint16_t point1, uint16_t point2) {
	if (point1 == point2) return { INF,0 };
	QList<uint16_t> roadIDs = wayPointMap.value(point1).GetRoadIds();
	for (int i = 0;i < roadIDs.size();i++) {
		Road roadID = roadMap.value(roadIDs[i]);
		if (point2 == roadID.u || point2 == roadID.v) {
			WayPoint P1 = wayPointMap.value(point1);
			WayPoint P2 = wayPointMap.value(point2);
			double distance = P1 - P2;
			return { distance , roadIDs[i]};
		}
	}
	return { INF,0 };
}

bool Algorithm::CheckSame(uint16_t point, PointList(&pointList)) {
	for (uint16_t i = 0;i < pointList.CheckList.size();i++) {
		if (point == pointList.CheckList[i]) {
			return true;
		}
	}
	return false;
}

uint16_t Algorithm::DeepSearch(uint16_t startPointID, uint16_t endPointID,uint16_t lastPointID, PointList& pointList) {
	if (startPointID == endPointID) {
		return 1;
	}
	
	if (CheckSame(startPointID, pointList)) {//剔除重复搜寻点（剔除回环与中间点重复）
		return 0;
	}

	pointList.CheckList.push_back(startPointID);

	int judge = 0;
	QList<uint16_t> roadIDs = wayPointMap.value(startPointID).GetRoadIds();
	for (int i = 0;i < roadIDs.size();i++) {
		Road roadID = roadMap.value(roadIDs[i]);
		uint16_t otherone;
		if (startPointID == roadID.u) {
			startPointID = roadID.u, otherone = roadID.v;
		}
		else {
			startPointID = roadID.v, otherone = roadID.u;
		}
		if (otherone != lastPointID) {//剔除尽头或回头
			judge = judge + DeepSearch(otherone, endPointID, startPointID, pointList);
		}
	}

	if (judge != 0 ) {
		/*邻接表录入信息*/
		bool same = true;
		for (uint16_t i = 0;i < pointList.PointNum;i++)
			if (startPointID == pointList.WayPointList[i])
				same = false;
		if (same) {
			pointList.WayPointList.push_back(startPointID);
			pointList.PointNum++;

			QList<double> tem;
			QList<uint16_t> temp;
			for (int i = 0;i < pointList.PointNum;i++) {
				tem.push_back(INF);
				temp.push_back(UINT16_MAX);
			}
			
			pointList.AdjTable.push_back(tem);
			pointList.RoadTable.push_back(temp);

			for (int i = 0;i < pointList.PointNum - 1;i++) {
				pointList.AdjTable[i].push_back(INF);
				pointList.RoadTable[i].push_back(UINT16_MAX);

				pair<double, uint16_t> tem = JudgeSameRoad(pointList.WayPointList[i], startPointID);

				pointList.AdjTable[i][pointList.PointNum - 1] = tem.first;
				pointList.AdjTable[pointList.PointNum - 1][i] = tem.first;

				pointList.RoadTable[i][pointList.PointNum - 1] = tem.second;
				pointList.RoadTable[pointList.PointNum - 1][i] = tem.second;
			}
		}
	}

	return judge;
}


AnswerList Algorithm::Method(uint16_t startPointID, PointList pointList) {
	/*
	*Dijistra算法实现
	*/

	AnswerList answerList;
	answerList.WayPointList = pointList.WayPointList;
	answerList.startPointID = startPointID;
	QList<bool> flag;//标记选中节点

	for (int i = 0;i < pointList.PointNum;i++) {
		answerList.dist.push_back(pointList.AdjTable[startPointID][i]);//源点初始化
		flag.push_back(false);
		if (answerList.dist[i] == INF)
			answerList.p.push_back(UINT16_MAX);
		else
			answerList.p.push_back(startPointID);
		answerList.p_road.push_back(UINT16_MAX);
	}
	answerList.dist[startPointID] = 0;
	flag[startPointID] = true;
	for (int i = 0;i < pointList.PointNum;i++) {
		double temp = INF, t = startPointID;
		for (int j = 0;j < pointList.PointNum;j++) {//寻找最短路径
			if (!flag[j] && answerList.dist[j] < temp) {
				t = j;
				temp = answerList.dist[j];
			}
		}
		if (t == startPointID) break;
		flag[t] = true;//标记选中
		for(int j=0;j< pointList.PointNum;j++)//更新路径
			if(!flag[j]&& pointList.AdjTable[t][j]<INF)
				if (answerList.dist[j] > answerList.dist[t] + pointList.AdjTable[t][j]) {
					answerList.dist[j] = answerList.dist[t] + pointList.AdjTable[t][j];
					answerList.p[j] = t;
					answerList.p_road[j] = pointList.RoadTable[t][j];
				}
	}
	return answerList;
}

QList<pair<uint16_t, uint16_t>> Algorithm::ReturnData(uint16_t endPointID, AnswerList answerList) {
	//输出数据
	QList<pair<uint16_t,uint16_t>> answer;

	double front;
	for (uint16_t i = 0;i < answerList.WayPointList.size();i++)
		if (answerList.WayPointList[i] == endPointID)
			front = i;

	stack<pair<uint16_t,uint16_t>>S;
	if (front == UINT16_MAX && endPointID != front)
		cout << "无路可达！" << endl;

	while (front != UINT16_MAX) {
		S.push({ front ,answerList.p_road[front]});
		front = answerList.p[front];
	}
	cout << "路径为： ";
	while (!S.empty()) {
		cout << answerList.WayPointList[S.top().first] << "--";
		answer.push_back({ answerList.WayPointList[S.top().first] ,S.top().second });
		S.pop();
	}
	return answer;
}