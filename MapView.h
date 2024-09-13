#pragma once
#include <QGraphicsView>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <qscrollbar.h>

#include "WayPointPixmapItem.h"
#include "RoadRectItem.h"
#include "SettingVarible.h"
#include "Definition.h"
#include "Algorithm.h"
#include "GlobalVariable.h"

class MapView : public QGraphicsView
{
public:
	MapView(QWidget* parent = nullptr);
	~MapView();

	void SetMap();
	void SetMap(QString mapPath);

	QPointF GetMousePoint();

	void _mousePressEvent(QMouseEvent* event);

	void AddWayPoint(uint16_t id);

	void AddRoad(uint16_t id);

	void DeleteWayPoint(uint16_t id);

	void MousePointHide();
	void MousePointShow();

	void ReadWayPoint();

protected:
	void wheelEvent(QWheelEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;

	void translate(int dx, int dy);

private:

	QPoint GetWidgetCenter();

	uint64_t GetTime();

	void SetMousePoint();
	void SetMousePoint(QPointF point);

private:

	QMap<uint16_t, WayPointPixmapItem*> wayPointMap;

	QMap<uint16_t, RoadRectItem*> roadItemMap;

	QPoint scrollBarPos;
	QPoint lastPos;
	QGraphicsPixmapItem* mousePointPixmapItem;
	QPointF mousePointCoordinate;
	uint64_t mousePressTime;
	QGraphicsScene* scene;
	QGraphicsPixmapItem* mapItem;
};
