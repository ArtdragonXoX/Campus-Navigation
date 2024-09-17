#include "Algorithm.h"
#include <iostream>//
using namespace GlobalVariable;
PointList Algorithm::DataPutIn(QList<uint16_t> (&WayPointList)) {
	/* 
	* ¼��V,�Ǽǵ�һ��pointNum
	*/
	PointList pointList;
	pointList.WayPointList = WayPointList;
	pointList.PointNum = pointList.WayPointList.size();

	return pointList;
}

PointList Algorithm::AddMiddlPoint(PointList pointList) {//��������
	/*
	* ������������������ص�,�������ڽӱ�
	*/
	QList<double> tem;//��ʼ���ڽӱ�
	for (int i = 0;i < pointList.PointNum;i++)
		tem.push_back(INF);
	for (int i = 0;i < pointList.PointNum;i++)
		pointList.AdjTable.push_back(tem);

	uint16_t searchNum = pointList.PointNum;
	for (uint16_t i = 0;i < searchNum;i++) {
		for (uint16_t j = i;j < searchNum;j++) {
			double judge = JudgeSameRoad(pointList.WayPointList[i], pointList.WayPointList[j]);
			if (judge==INF) {
				DeepSearch(pointList.WayPointList[i], pointList.WayPointList[j],0,pointList);
				pointList.CheckList.clear();
			}
			else {
				pointList.AdjTable[i][j] = judge;
				pointList.AdjTable[j][i] = judge;
			}
		}
	}
	return pointList;
}

double Algorithm::JudgeSameRoad(uint16_t point1, uint16_t point2) {
	if (point1 == point2) return INF;
	QList<uint16_t> roadIDs = wayPointMap.value(point1).roadIds;
	for (int i = 0;i < roadIDs.size();i++) {
		Road roadID = roadMap.value(roadIDs[i]);
		if (point2 == roadID.u || point2 == roadID.v) {
			WayPoint P1 = wayPointMap.value(point1);
			WayPoint P2 = wayPointMap.value(point2);
			double distance = P1 - P2;
			return distance;
		}
	}
	return INF;
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
	
	if (CheckSame(startPointID, pointList)) {//�޳��ظ���Ѱ�㣨�޳��ػ����м���ظ���
		return 0;
	}

	pointList.CheckList.push_back(startPointID);

	int judge = 0;
	QList<uint16_t> roadIDs = wayPointMap.value(startPointID).roadIds;
	for (int i = 0;i < roadIDs.size();i++) {
		Road roadID = roadMap.value(roadIDs[i]);
		uint16_t otherone;
		if (startPointID == roadID.u) {
			startPointID = roadID.u, otherone = roadID.v;
		}
		else {
			startPointID = roadID.v, otherone = roadID.u;
		}
		if (otherone != lastPointID) {//�޳���ͷ���ͷ
			judge = judge + DeepSearch(otherone, endPointID, startPointID, pointList);
		}
	}

	if (judge != 0 ) {
		/*�ڽӱ�¼����Ϣ*/
		bool same = true;
		for (uint16_t i = 0;i < pointList.PointNum;i++)
			if (startPointID == pointList.WayPointList[i])
				same = false;
		if (same) {
			pointList.WayPointList.push_back(startPointID);
			pointList.PointNum++;

			QList<double> tem;
			for (int i = 0;i < pointList.PointNum;i++) {
				tem.push_back(INF);
			}
			pointList.AdjTable.push_back(tem);
			for (int i = 0;i < pointList.PointNum - 1;i++) {
				pointList.AdjTable[i].push_back(INF);
				double tem = JudgeSameRoad(pointList.WayPointList[i], startPointID);
				pointList.AdjTable[i][pointList.PointNum - 1] = tem;
				pointList.AdjTable[pointList.PointNum - 1][i] = tem;
			}
		}
	}

	return judge;
}


AnswerList Algorithm::Method(uint16_t startPointID, PointList pointList) {
	/*
	*Dijistra�㷨ʵ��
	*/

	AnswerList answerList;
	answerList.WayPointList = pointList.WayPointList;
	answerList.startPointID = startPointID;
	QList<bool> flag;//���ѡ�нڵ�

	for (int i = 0;i < pointList.PointNum;i++) {
		answerList.dist.push_back(pointList.AdjTable[startPointID][i]);//Դ���ʼ��
		flag.push_back(false);
		if (answerList.dist[i] == INF)
			answerList.p.push_back(UINT16_MAX);
		else
			answerList.p.push_back(startPointID);
	}
	answerList.dist[startPointID] = 0;
	flag[startPointID] = true;
	for (int i = 0;i < pointList.PointNum;i++) {
		double temp = INF, t = startPointID;
		for (int j = 0;j < pointList.PointNum;j++) {//Ѱ�����·��
			if (!flag[j] && answerList.dist[j] < temp) {
				t = j;
				temp = answerList.dist[j];
			}
		}
		if (t == startPointID) break;
		flag[t] = true;//���ѡ��
		for(int j=0;j< pointList.PointNum;j++)//����·��
			if(!flag[j]&& pointList.AdjTable[t][j]<INF)
				if (answerList.dist[j] > answerList.dist[t] + pointList.AdjTable[t][j]) {
					answerList.dist[j] = answerList.dist[t] + pointList.AdjTable[t][j];
					answerList.p[j] = t;
				}
	}
	return answerList;
}

QList<uint16_t> Algorithm::ReturnData(uint16_t endPointID, AnswerList answerList) {
	//�������
	QList<uint16_t> answer;

	double front;
	for (uint16_t i = 0;i < answerList.WayPointList.size();i++)
		if (answerList.WayPointList[i] == endPointID)
			front = i;

	stack<uint16_t>S;
	if (front == UINT16_MAX && endPointID != front)
		cout << "��·�ɴ" << endl;

	while (front != UINT16_MAX) {
		S.push(front);
		front = answerList.p[front];
	}
	cout << "·��Ϊ�� ";
	while (!S.empty()) {
		cout << answerList.WayPointList[S.top()] << "--";
		answer.push_back(answerList.WayPointList[S.top()]);
		S.pop();
	}
	return answer;
}