#include "MapView.h"

MapView::MapView(QWidget* parent) : QGraphicsView(parent)
{
	scene = new QGraphicsScene(this);
	setScene(scene);
	SetMap();
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
	scene->addItem(mapItem);
	resetTransform();
}

void MapView::wheelEvent(QWheelEvent* event)
{
	double angle = event->angleDelta().y();
	double factor = qPow(1.0015, angle);
	scale(factor, factor);
}

void MapView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		lastPos = event->pos();
	}
	printf("lastPos: %d, %d\n", lastPos.x(), lastPos.y());
}

void MapView::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		QPointF delta = mapToScene(event->pos()) - mapToScene(lastPos);
		translate(delta.x(), delta.y());
	}
	//QGraphicsView::mouseMoveEvent(event);
}

void MapView::translate(int dx, int dy)
{
	this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() - dx);
	this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - dy);
}

uint64_t MapView::GetTime()
{
	return QDateTime::currentDateTime().toMSecsSinceEpoch();
}