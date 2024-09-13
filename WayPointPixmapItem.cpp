#include "WayPointPixmapItem.h"

WayPointPixmapItem::WayPointPixmapItem(uint16_t id, QGraphicsItem* parent)
{
	const auto& data = GlobalVariable::wayPointMap.value(id);
	SetType(data.type);
	SetCenterPos(data.coord);
	this->id = id;
	printf("id:%d\n", id);
	setScale(0.25);
}

void WayPointPixmapItem::SetType(WayPointType type)
{
	this->type = type;
	if (type == Buildings)
	{
		setPixmap(QPixmap("./resource/Buildings.png"));
		show();
	}
	else
	{
		setPixmap(QPixmap("./resource/RoadNode.png"));
		//hide();
	}
}

WayPointType WayPointPixmapItem::Type() const
{
	return type;
}

void WayPointPixmapItem::SetCenterPos(Coord coord)
{
	SetCenterPos(QPointF(coord.x, coord.y));
}

void WayPointPixmapItem::SetCenterPos(QPointF pos)
{
	centerPos = pos;
	setPos();
}

QPointF WayPointPixmapItem::CenterPos() const
{
	return centerPos;
}

uint16_t WayPointPixmapItem::ID() const
{
	return id;
}

void WayPointPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		signalHandler->EmitWayPointItemClicked(this->id);
	}
}

void WayPointPixmapItem::setPos()
{
	auto pos = GetIconPos();
	QGraphicsPixmapItem::setPos(pos);
}

QPointF WayPointPixmapItem::GetIconPos() const
{
	//return centerPos;
	return centerPos - QPointF(boundingRect().width() / 8 - 22, 8);
}
