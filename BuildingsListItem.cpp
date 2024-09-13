#include "BuildingsListItem.h"

BuildingsListItem::BuildingsListItem(uint16_t buildingId, QString buildingName, QWidget* parent) : QWidget(parent)
{
	ui.setupUi(this);
	SetBuildingId(buildingId);
	SetBuildingName(buildingName);
	widgetItem = new QListWidgetItem();
	//widgetItem->setSizeHint(itemSize);
	widgetItem->setSizeHint(QSize(100, 30));
	widgetItem->setData(Qt::UserRole, QString::number(buildingId));
	InitConnect();
}

BuildingsListItem::BuildingsListItem(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

BuildingsListItem::~BuildingsListItem()
{
	delete widgetItem;
}

void BuildingsListItem::InitConnect()
{
	connect(ui.pushButton, &QPushButton::clicked, this, &BuildingsListItem::Delete);
}

void BuildingsListItem::Delete()
{
	signalHandler->EmitWayPointDeleteInList(buildingId);
	delete this;
}

void BuildingsListItem::SetBuildingId(uint16_t buildingId)
{
	this->buildingId = buildingId;
}

void BuildingsListItem::SetBuildingName(QString buildingName)
{
	ui.name->setText(buildingName);
}

uint16_t BuildingsListItem::ID()
{
	return buildingId;
}

QListWidgetItem* BuildingsListItem::GetWidgetItem()
{
	return widgetItem;
}
