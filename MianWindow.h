#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MianWindow.h"

#include "MapView.h"
#include "Definition.h"
#include "GlobalVariable.h"
#include "SignalHandler.h"
#include "BuildingsListItem.h"

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

	void AddRoad();
	void AddRoad(Road road);

	void AddWayPointWidgetHide();
	void AddWayPointWidgetShow();

	void userWidgetHide();
	void userWidgetShow();

	void DeleteWayPoint(uint16_t id);

	void WayPointItemClicked(uint16_t id);

	void AddBuidingsToList();
	void ClearBuildingList();
	void DeleteBuildingInList(uint16_t id);
	void Query();

	void ExportWayPoint();
	void ExportRoad();

private:
	uint16_t m_id = 0;

	Ui::MianWindowClass ui;
};
