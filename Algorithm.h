#pragma once

//�㷨��

#include "Definition.h"
#include "GlobalVariable.h"

#define INF 65535//short���

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
	void AddMiddlPoint();//����δ����;����
	void MakeData(uint16_t firstpoint, uint16_t endpoint);//������������
	void Method();
	void Method(uint16_t u);//Dijkatra�㷨ʵ��
	void ReturnData();//����������
	void DeepSearch(uint16_t point, uint16_t* next);
};