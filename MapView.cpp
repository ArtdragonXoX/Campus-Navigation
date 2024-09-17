#include "MapView.h"

MapView::MapView(QWidget* parent) : QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);
	SetMap();
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	mousePointPixmapItem = new QGraphicsPixmapItem(QPixmap("./resource/pushpin.png"));
	mousePointPixmapItem->setZValue(2);
	mousePointPixmapItem->setScale(0.25);
	scene->addItem(mousePointPixmapItem);
	MousePointHide();
	centerOn(500, 500);
}

MapView::~MapView()
{
}

void MapView::SetMap()
{
	//SetMap("qrc:/map/resource/mapimage.jpg");
	SetMap("./resource/mapimage.jpg");
}

void MapView::SetMap(QString mapPath)
{
	QPixmap pixmap(mapPath);
	mapItem = new QGraphicsPixmapItem(pixmap);
	mapItem->setZValue(-1);
	scene->addItem(mapItem);
	resetTransform();
}

void MapView::wheelEvent(QWheelEvent* event)
{
	double angle = event->angleDelta().y();
	double factor = qPow(1.0015, angle);
	scale(factor, factor);
}

void MapView::_mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		scrollBarPos.setX(horizontalScrollBar()->value());
		scrollBarPos.setY(verticalScrollBar()->value());
	}
	//printf("lastPos: %d, %d\n", lastPos.x(), lastPos.y());
	if (event->buttons() & Qt::RightButton)
	{
		mousePointCoordinate = mapToScene(event->pos());
		//printf("mousePointCoordinate: %f, %f\n", mousePointCoordinate.x(), mousePointCoordinate.y());
		SetMousePoint();
	}
	lastPos = event->pos();
}

void MapView::AddWayPoint(uint16_t id)
{
	auto wayPointItem = new WayPointPixmapItem(id);
	wayPointMap.insert(id, wayPointItem);
	scene->addItem(wayPointItem);
}

void MapView::AddRoad(uint16_t id)
{
	auto roadItem = new RoadRectItem(id);
	roadItemMap.insert(id, roadItem);
	scene->addItem(roadItem);
	if (!GlobalVariable::wayPointMap.value(GlobalVariable::roadMap.value(id).u).roadIds.contains(id))
		GlobalVariable::wayPointMap.value(GlobalVariable::roadMap.value(id).u).roadIds.append(id);
	if (!GlobalVariable::wayPointMap.value(GlobalVariable::roadMap.value(id).v).roadIds.contains(id))
		GlobalVariable::wayPointMap.value(GlobalVariable::roadMap.value(id).v).roadIds.append(id);
}

void MapView::DeleteWayPoint(uint16_t id)
{
	auto wayPointItem = wayPointMap.value(id);
	if (wayPointItem)
	{
		scene->removeItem(wayPointItem);
		wayPointMap.remove(id);
	}
}

void MapView::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		QPoint delta = event->pos() - lastPos;
		translate(delta.x(), delta.y());
	}
	//QGraphicsView::mouseMoveEvent(event);
}

void MapView::translate(int dx, int dy)
{
	this->horizontalScrollBar()->setValue(scrollBarPos.x() - dx);
	this->verticalScrollBar()->setValue(scrollBarPos.y() - dy);
}

QPoint MapView::GetWidgetCenter()
{
	return QPoint(width() / 2, height() / 2);
}

uint64_t MapView::GetTime()
{
	return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

void MapView::SetMousePoint()
{
	SetMousePoint(mousePointCoordinate);
	MousePointShow();
}

void MapView::SetMousePoint(QPointF point)
{
	mousePointPixmapItem->setPos(GetMousePoint());
}

QPointF MapView::GetMousePoint()
{
	return mousePointCoordinate - QPointF(mousePointPixmapItem->boundingRect().width() / 8, mousePointPixmapItem->boundingRect().height() / 8 + 16);
}

void MapView::MousePointHide()
{
	mousePointPixmapItem->hide();
}

void MapView::MousePointShow()
{
	mousePointPixmapItem->show();
}

void MapView::ReadWayPoint()
{
	for (auto& wayPointItem : GlobalVariable::wayPointMap)
	{
		AddWayPoint(wayPointItem.id);
		printf("id: %d\n", wayPointItem.id);
	}
}

void MapView::ReadRoad()
{
	for (auto& roadItem : GlobalVariable::roadMap)
	{
		AddRoad(roadItem.id);
		printf("id: %d\n", roadItem.id);
	}
}
