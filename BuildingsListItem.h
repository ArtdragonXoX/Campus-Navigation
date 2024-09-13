#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "ui_BuildingsListItem.h"

#include "SignalHandler.h"

class BuildingsListItem : public QWidget
{
	Q_OBJECT

public:
	BuildingsListItem(uint16_t buildingId, QString buildingName, QWidget* parent = nullptr);
	BuildingsListItem(QWidget* parent = nullptr);
	~BuildingsListItem();

	void InitConnect();

	void Delete();

	void SetBuildingId(uint16_t buildingId);
	void SetBuildingName(QString buildingName);

	uint16_t ID();

	QListWidgetItem* GetWidgetItem();

private:
	QListWidgetItem* widgetItem = nullptr;
	uint16_t buildingId;
	Ui::BuildingsListItemClass ui;
};
