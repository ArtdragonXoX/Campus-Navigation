#pragma once
#include <QMap>
#include "Definition.h"

//全局变量声明
namespace GlobalVariable
{
	extern QMap <uint16_t, WayPoint> wayPointMap; //路点列表
	extern QMap <uint16_t, Road> roadMap; //道路列表
}