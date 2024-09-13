#pragma once
#include <QObject>

class SignalHandler : public QObject
{
	Q_OBJECT
public:
	SignalHandler(QObject* parent = nullptr);
	~SignalHandler();

	void EmitWayPointItemClicked(uint16_t id);

	void EmitWayPointDeleteInList(uint16_t id);

signals:
	void WayPointItemClicked(uint16_t id);
	void WayPointDeleteInList(uint16_t id);
};

extern SignalHandler* signalHandler;