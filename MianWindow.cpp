#include "MianWindow.h"

MianWindow::MianWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	AddWayPointWidgetHide();
	InitConnection();
	userWidgetHide();
	FileIO::ReadMapData();
	ui.mapWidget->ReadWayPoint();
	ui.mapWidget->ReadRoad();
}

MianWindow::~MianWindow()
{}

void MianWindow::InitConnection()
{
	connect(ui.confirmPushButton, &QPushButton::clicked, this, qOverload<>(&MianWindow::AddWayPoint));
	connect(ui.cancelPushButton, &QPushButton::clicked, this, &MianWindow::AddWayPointWidgetHide);
	connect(ui.addRoadCancelPushButton, &QPushButton::clicked, this, &MianWindow::AddWayPointWidgetHide);
	connect(ui.addRoadConfirmPushButton, &QPushButton::clicked, this, qOverload<>(&MianWindow::AddRoad));
	connect(ui.addBuildingsToListPushButton, &QPushButton::clicked, this, &MianWindow::AddBuidingsToList);
	connect(signalHandler, &SignalHandler::WayPointItemClicked, this, &MianWindow::WayPointItemClicked);
	connect(ui.buildingsListClearPushButton, &QPushButton::clicked, this, &MianWindow::ClearBuildingList);
	connect(ui.buildingsListQueryPushButton, &QPushButton::clicked, this, &MianWindow::Query);
	connect(ui.exportWayPointPushButton, &QPushButton::clicked, this, &MianWindow::ExportWayPoint);
	connect(ui.exportRoadPushButton, &QPushButton::clicked, this, &MianWindow::ExportRoad);
}

void MianWindow::mousePressEvent(QMouseEvent* event)
{
	ui.mapWidget->_mousePressEvent(event);
	ui.mapWidget->MousePointHide();
	if (event->button() == Qt::RightButton)
	{
		QPointF pos = ui.mapWidget->GetMousePoint();
		ui.XDoubleSpinBox->setValue(pos.x());
		ui.YDoubleSpinBox->setValue(pos.y());
		printf("X:%f,Y:%f\n", pos.x(), pos.y());
		ui.mapWidget->MousePointShow();
	}
	userWidgetHide();
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
	WayPoint wp;
	wp.id = GlobalVariable::wayPointMap.isEmpty() ? 0 : GlobalVariable::wayPointMap.lastKey() + 1;
	wp.name = ui.addLandMarkName->text();
	wp.coord = { ui.XDoubleSpinBox->value(),ui.YDoubleSpinBox->value() };
	wp.type = ui.wayPointComboBox->currentIndex() ? RoadNode : Buildings;
	AddWayPoint(wp);
	ui.addLandMarkName->clear();
	ui.wayPointComboBox->setCurrentIndex(0);
}

void MianWindow::AddWayPoint(WayPoint wp)
{
	GlobalVariable::wayPointMap.insert(wp.id, wp);
	ui.mapWidget->AddWayPoint(wp.id);
	AddWayPointWidgetHide();
}

void MianWindow::AddRoad()
{
	Road road;
	road.id = GlobalVariable::roadMap.isEmpty() ? 0 : GlobalVariable::roadMap.lastKey() + 1;
	road.u = ui.wayPointID1spinBox->value();
	road.v = ui.wayPointID2spinBox->value();
	AddRoad(road);
}

void MianWindow::AddRoad(Road road)
{
	GlobalVariable::roadMap.insert(road.id, road);
	ui.mapWidget->AddRoad(road.id);
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

void MianWindow::userWidgetHide()
{
	ui.buildingsInfoWidget->hide();
}

void MianWindow::userWidgetShow()
{
	ui.buildingsInfoWidget->show();
}

void MianWindow::DeleteWayPoint(uint16_t id)
{
	GlobalVariable::wayPointMap.remove(id);
	ui.mapWidget->DeleteWayPoint(id);
}

void MianWindow::WayPointItemClicked(uint16_t id)
{
	userWidgetShow();
	m_id = id;
	ui.buildingsInfoID->setText(QString::number(id));
	ui.buildingsInfoName->setText(GlobalVariable::wayPointMap.value(id).name);
}

void MianWindow::AddBuidingsToList()
{
	BuildingsListItem* item = new BuildingsListItem(m_id, GlobalVariable::wayPointMap.value(m_id).name);
	ui.buildingsListWidget->addItem(item->GetWidgetItem());
	ui.buildingsListWidget->setItemWidget(item->GetWidgetItem(), item);
}

void MianWindow::ClearBuildingList()
{
	int num = ui.buildingsListWidget->count();
	for (int i = 0; i < num; i++)
	{
		delete ui.buildingsListWidget->itemWidget(ui.buildingsListWidget->item(0));
	}
}

void MianWindow::DeleteBuildingInList(uint16_t id)
{
}

void MianWindow::Query()
{
	QList<uint16_t> wayPointList;
	for (int i = 0; i < ui.buildingsListWidget->count(); i++)
	{
		BuildingsListItem* item = (BuildingsListItem*)ui.buildingsListWidget->itemWidget(ui.buildingsListWidget->item(i));
		wayPointList.append(item->ID());
	}
	//ртобн╙╡Бйт
	Algorithm A;
	A.ReturnData(wayPointList[wayPointList.size()-1], A.Method(wayPointList[0], A.AddMiddlPoint(A.DataPutIn(wayPointList))));
}

void MianWindow::ExportWayPoint()
{
	FileIO::WriteWayPointData();
}

void MianWindow::ExportRoad()
{
	FileIO::WriteRoadData();
}
