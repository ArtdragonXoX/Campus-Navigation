#include "Algorithm.h"

Algorithm::Algorithm(uint16_t firstpoint,uint16_t endpoint) {
	/*
	* ¼��V,�Ǽǵ�һ��pointNum����ִ���������з���
	*/

	AddMiddlPoint();
	MakeData(firstpoint,endpoint);
	Method(firstpoint);
}

void Algorithm::AddMiddlPoint() {
	/*
	* ���������������V,�Ǽǵ�һ��pointNum
	*/
	uint16_t *head,*next;//��������ͷ
	next = head;
	DeepSearch();
}

void Algorithm::DeepSearch(uint16_t point,uint16_t* next) {

}


void Algorithm::MakeData(uint16_t firstpoint, uint16_t endpoint) {
	/*
	* ���ø��º��V��V-S�����ڽӱ�ʹ��new�����ڽӱ�
	*/
	Edge = new uint16_t*[pointNum];
	for (int i = 0;i < pointNum;i++) {
		Edge[i] = new uint16_t[pointNum];
		for (int j = 0;j < pointNum;j++) {//�����Ƿ���Ҫ��Ӧ�ò���ҪǶ��ѭ��
			/*
			* ¼����ڽ�����
			*/
		}
	}
}

void Algorithm::Method(uint16_t u) {
	/*
	* �㷨ʵ��
	*/

	u = 0;//������Դ��
	uint16_t* flag = new uint16_t[pointNum];//���ѡ�нڵ�
	uint16_t* p = new uint16_t[pointNum];//��¼Դ�㵽���ڵ����̾���

	for (int i = 0;i < pointNum;i++) {
		dist[i] = Edge[u][i];//Դ���ʼ��
		flag[i] = false;
		if (dist[i] == INF)
			p[i] = -1;
		else
			p[i] = u;
	}
	dist[u] = 0;
	flag[u] = true;
	for (int i = 0;i < pointNum;i++) {
		uint16_t temp = INF, t = u;
		for (int j = 0;j < pointNum;j++) {//Ѱ�����·��
			if (!flag[j] && dist[j] < temp) {
				t = j;
				temp = dist[j];
			}
		}
		if (t == u) return;//�Ƿ���Ҫ�������������
		flag[t] = true;//���ѡ��
		for(int j=0;j<pointNum;j++)//����·��
			if(!flag[j]&&Edge[t][j]<INF)
				if (dist[j] > dist[t] + Edge[t][j]) {
					dist[j] = dist[t] + Edge[t][j];
					p[j] = t;
				}
	}
}

void Algorithm::ReturnData() {
	//������ݣ�˳����տռ�,�ȴ�����
	path;
}