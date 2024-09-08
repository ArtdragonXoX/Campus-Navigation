#pragma once

//算法类

#include "Definition.h"
#include "GlobalVariable.h"

#define INF 65535//short最大

class Algorithm
{
private:
	uint16_t pointNum;
	uint16_t* V;
	uint16_t* path;
	uint16_t* dist;
	uint16_t** Edge;

	Algorithm(uint16_t firstpoint,uint16_t endpoint);

public:
	void AddMiddlPoint();//补充未给予途径点
	void MakeData(uint16_t firstpoint, uint16_t endpoint);//制作所需数据
	void Method();
	void Method(uint16_t u);//Dijkatra算法实现
	void ReturnData();//输出结果数据
	void DeepSearch(uint16_t point, uint16_t* next);
};