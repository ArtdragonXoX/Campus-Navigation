#pragma once
#include <QGraphicsView>
#include <QTime>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <qscrollbar.h>

#include "SettingVarible.h"
#include "Definition.h"

class MapView : public QGraphicsView
{
public:
	MapView(QWidget* parent = nullptr);
	~MapView();

	void SetMap();
	void SetMap(QString mapPath);
protected:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	//void mouseReleaseEvent(QMouseEvent* event) override;

	void translate(int dx, int dy);

private:
	uint64_t GetTime();
private:
	QPoint lastPos;
	uint64_t mousePressTime;
	QGraphicsScene* scene;
	QGraphicsPixmapItem* mapItem;
};
