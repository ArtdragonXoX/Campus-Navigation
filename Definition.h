#pragma once
#include <cstdint>
#include <QString>
#include <QList>

//������������

struct Coord;
struct WayPoint;
struct Road;

//���꣬��ͼ���½�Ϊԭ��
struct Coord
{
	double x;//�޸�������
	double y;
	double_t operator - (const Coord& other) const
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
};

//·��������
enum WayPointType
{
	Buildings,//������
	RoadNode//��·�ڵ�
};

//·����
struct WayPoint
{
	uint16_t id;
	QString name;
	Coord coord;
	WayPointType type;
	QList<uint16_t> roadIds;

	double_t operator - (const WayPoint& other) const
	{
		return coord - other.coord;
	}
	double_t operator - (const Coord& other) const
	{
		return coord - other;
	}
};

//��·
struct Road
{
	uint16_t id;

	//����·�����id
	uint16_t u;
	uint16_t v;
};
