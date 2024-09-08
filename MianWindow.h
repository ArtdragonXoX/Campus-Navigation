#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MianWindow.h"

#include "MapView.h"
#include "Definition.h"

class MianWindow : public QMainWindow
{
	Q_OBJECT

public:
	MianWindow(QWidget* parent = nullptr);
	~MianWindow();

	void InitConnection();

	void mousePressEvent(QMouseEvent* event) override;

	void keyPressEvent(QKeyEvent* event) override;

	void AddWayPoint();
	void AddWayPoint(WayPoint wp);

	void AddWayPointWidgetHide();
	void AddWayPointWidgetShow();

private:
	Ui::MianWindowClass ui;
};
