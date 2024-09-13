#include "SignalHandler.h"

SignalHandler::SignalHandler(QObject* parent) : QObject(parent)
{
}

SignalHandler::~SignalHandler()
{
}

void SignalHandler::EmitWayPointItemClicked(uint16_t id)
{
	emit WayPointItemClicked(id);
}

void SignalHandler::EmitWayPointDeleteInList(uint16_t id)
{
	emit WayPointDeleteInList(id);
}

SignalHandler* signalHandler = new SignalHandler();