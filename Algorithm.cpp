#include "Algorithm.h"

Algorithm::Algorithm(uint16_t firstpoint,uint16_t endpoint) {
	/*
	* 录入V,登记第一个pointNum，并执行以下所有方法
	*/

	AddMiddlPoint();
	MakeData(firstpoint,endpoint);
	Method(firstpoint);
}

void Algorithm::AddMiddlPoint() {
	/*
	* 采用深度搜索补充V,登记第一个pointNum
	*/
	uint16_t *head,*next;//补充链表头
	next = head;
	DeepSearch();
}

void Algorithm::DeepSearch(uint16_t point,uint16_t* next) {

}


void Algorithm::MakeData(uint16_t firstpoint, uint16_t endpoint) {
	/*
	* 利用更新后的V，V-S制作邻接表，使用new制作邻接表
	*/
	Edge = new uint16_t*[pointNum];
	for (int i = 0;i < pointNum;i++) {
		Edge[i] = new uint16_t[pointNum];
		for (int j = 0;j < pointNum;j++) {//这里是否需要？应该不需要嵌套循环
			/*
			* 录入各邻接数据
			*/
		}
	}
}

void Algorithm::Method(uint16_t u) {
	/*
	* 算法实现
	*/

	u = 0;//先设置源点
	uint16_t* flag = new uint16_t[pointNum];//标记选中节点
	uint16_t* p = new uint16_t[pointNum];//记录源点到各节点的最短距离

	for (int i = 0;i < pointNum;i++) {
		dist[i] = Edge[u][i];//源点初始化
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
		for (int j = 0;j < pointNum;j++) {//寻找最短路径
			if (!flag[j] && dist[j] < temp) {
				t = j;
				temp = dist[j];
			}
		}
		if (t == u) return;//是否需要处理特殊情况？
		flag[t] = true;//标记选中
		for(int j=0;j<pointNum;j++)//更新路径
			if(!flag[j]&&Edge[t][j]<INF)
				if (dist[j] > dist[t] + Edge[t][j]) {
					dist[j] = dist[t] + Edge[t][j];
					p[j] = t;
				}
	}
}

void Algorithm::ReturnData() {
	//输出数据，顺便回收空间,等待调用
	path;
}