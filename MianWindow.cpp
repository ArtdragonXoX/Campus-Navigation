#include "MianWindow.h"

MianWindow::MianWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	AddWayPointWidgetHide();
	InitConnection();
}

MianWindow::~MianWindow()
{}

void MianWindow::InitConnection()
{
	connect(ui.confirmPushButton, &QPushButton::clicked, this, qOverload<>(&MianWindow::AddWayPoint));
	connect(ui.cancelPushButton, &QPushButton::clicked, this, &MianWindow::AddWayPointWidgetHide);
}

void MianWindow::mousePressEvent(QMouseEvent* event)
{
	ui.mapWidget->_mousePressEvent(event);
	if (event->button() == Qt::RightButton)
	{
		QPointF pos = ui.mapWidget->GetMousePoint();
		ui.XDoubleSpinBox->setValue(pos.x());
		ui.YDoubleSpinBox->setValue(pos.y());
	}
}

void MianWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_A)
	{
		AddWayPointWidgetShow();
	}
}

void MianWindow::AddWayPoint()
{
	AddWayPoint(WayPoint());
}

void MianWindow::AddWayPoint(WayPoint wp)
{
	AddWayPointWidgetHide();
}

void MianWindow::AddWayPointWidgetHide()
{
	ui.addWayPointWidget->hide();
}

void MianWindow::AddWayPointWidgetShow()
{
	ui.addWayPointWidget->show();
}