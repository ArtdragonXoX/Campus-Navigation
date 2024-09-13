#include "RoadRectItem.h"

RoadRectItem::RoadRectItem(uint16_t id, QGraphicsItem* parent)
{
	auto road = GlobalVariable::roadMap.value(id);
	new(this) RoadRectItem(road.u, road.v, parent);
}

RoadRectItem::RoadRectItem(uint16_t start, uint16_t end, QGraphicsItem* parent)
{
	auto u = GlobalVariable::wayPointMap.value(start).ToQPointF();
	auto v = GlobalVariable::wayPointMap.value(end).ToQPointF();
	new(this) RoadRectItem(u, v, parent);
}

RoadRectItem::RoadRectItem(QPointF start, QPointF end, QGraphicsItem* parent)
{
	new(this) QGraphicsRectItem(0, 0, m_width, Coord(start) - end, parent);
	setPos(start);
	rotate(start, end);
	QBrush brush(Qt::blue);
	setBrush(brush);
	QPen pen(Qt::blue);
	setPen(pen);
}

void RoadRectItem::setPos(QPointF pos)
{
	pos += QPointF(20, 40);
	QGraphicsRectItem::setPos(pos);
}

void RoadRectItem::rotate(QPointF start, QPointF end)
{
	QVector2D vec(end - start);
	QVector2D _v(QPointF(0, Coord(start) - end));
	QTransform transform;
	auto dot = QVector2D::dotProduct(vec, _v);
	auto cos = dot / (vec.length() * _v.length());
	auto angle = acos(cos) * 180 / M_PI;
	if (end.x() > start.x())
		angle = -angle;
	setRotation(angle);
}
