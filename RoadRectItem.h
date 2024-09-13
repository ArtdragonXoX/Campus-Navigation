#pragma once
#include <QGraphicsRectItem>
#include <QVector2D>
#include <QBrush>
#include <QPen>

#include "Definition.h"
#include "GlobalVariable.h"

class RoadRectItem :
	public QGraphicsRectItem
{
public:
	RoadRectItem(uint16_t id, QGraphicsItem* parent = nullptr);
	RoadRectItem(uint16_t start, uint16_t end, QGraphicsItem* parent = nullptr);
	RoadRectItem(QPointF start, QPointF end, QGraphicsItem* parent = nullptr);
	~RoadRectItem() = default;

protected:
	void setPos(QPointF pos);

	void rotate(QPointF start, QPointF end);

private:
	double m_width = 5.0;
};
