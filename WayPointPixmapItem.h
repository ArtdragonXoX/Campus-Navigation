#pragma once
#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>

#include "Algorithm.h"
#include "Definition.h"
#include "GlobalVariable.h"
#include "SignalHandler.h"

class WayPointPixmapItem :
	public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	WayPointPixmapItem(uint16_t id, QGraphicsItem* parent = nullptr);
	~WayPointPixmapItem() = default;

	void SetType(WayPointType type);
	WayPointType Type() const;

	void SetCenterPos(Coord coord);
	void SetCenterPos(QPointF pos);

	QPointF CenterPos() const;

	uint16_t ID() const;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

	void setPos();

private:
	QPointF GetIconPos() const;

private:
	uint16_t id;
	QPointF centerPos;
	WayPointType type;
};
