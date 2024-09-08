#pragma once
#include <QGraphicsView>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <qscrollbar.h>

#include "SettingVarible.h"
#include "Definition.h"
#include "Algorithm.h"

class MapView : public QGraphicsView
{
public:
	MapView(QWidget* parent = nullptr);
	~MapView();

	void SetMap();
	void SetMap(QString mapPath);

	QPointF GetMousePoint();

	void _mousePressEvent(QMouseEvent* event);

protected:
	void wheelEvent(QWheelEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;

	void translate(int dx, int dy);

private:

	QPoint GetWidgetCenter();

	uint64_t GetTime();

	void SetMousePoint();
	void SetMousePoint(QPointF point);

	void MousePointHide();
	void MousePointShow();

private:
	QPoint scrollBarPos;
	QPoint lastPos;
	QGraphicsPixmapItem* mousePointPixmapItem;
	QPointF mousePointCoordinate;
	uint64_t mousePressTime;
	QGraphicsScene* scene;
	QGraphicsPixmapItem* mapItem;
};
