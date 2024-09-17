#pragma once

#include <cstdint>
#include <QString>
#include <QList>
#include <QPointF>

using namespace std;

//定义数据类型

struct Coord;
struct WayPoint;
struct Road;

//坐标，地图左下角为原点
struct Coord
{
	double_t x;
	double_t y;
	double_t operator - (const Coord& other) const
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
	double_t operator - (const QPointF& other) const
	{
		auto otherCoord = Coord(other.x(), other.y());
		return *this - otherCoord;
	}

	Coord() : x(0), y(0) {}
	Coord(double_t x, double_t y) : x(x), y(y) {}
	Coord(const QPointF& point)
	{
		x = point.x();
		y = point.y();
	}
};

//路径点类型
enum WayPointType
{
	Buildings,//建筑物
	RoadNode//道路节点
};

//路径点
struct WayPoint
{
	uint16_t id;
	QString name;
	Coord coord;
	WayPointType type;
	QList<uint16_t> roadIds;

	QPointF ToQPointF()
	{
		return QPointF(coord.x, coord.y);
	}

	double_t operator - (const WayPoint& other) const
	{
		return coord - other.coord;
	}
	double_t operator - (const Coord& other) const
	{
		return coord - other;
	}
};

//道路
struct Road
{
	uint16_t id;

	//两个路径点的id
	uint16_t u;
	uint16_t v;
};
