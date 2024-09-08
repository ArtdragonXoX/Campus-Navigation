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
	mousePointPixmapItem->setScale(0.5);
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
	return mousePointCoordinate - QPointF(mousePointPixmapItem->boundingRect().width() / 4, mousePointPixmapItem->boundingRect().height() / 2 - 20);
}

void MapView::MousePointHide()
{
	mousePointPixmapItem->hide();
}

void MapView::MousePointShow()
{
	mousePointPixmapItem->show();
}
