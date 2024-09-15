#include "FileIO.h"
#include "GlobalVariable.h"
using namespace GlobalVariable;

void FileIO::WriteMapData()
{
	WriteMapData(GlobalVariable::wayPointMap, GlobalVariable::roadMap);
}

//写入地图数据
void FileIO::WriteMapData(QMap <uint16_t, WayPoint> pointMap, QMap <uint16_t, Road> roadMap)
{
	QJsonObject obj_point = QMap_WayPointToJson(pointMap);
	QJsonObject obj_road = QMap_RoadToJson(roadMap);
	//写入waypoint.json文件
	WriteToJsonFile(obj_point, "./data/points.json");
	//写入road.json文件
	WriteToJsonFile(obj_road, "./data/roads.json");
}

void FileIO::WriteWayPointData()
{
	QJsonObject obj_point = QMap_WayPointToJson(GlobalVariable::wayPointMap);
	WriteToJsonFile(obj_point, "./data/points.json");
}

void FileIO::WriteRoadData()
{
	QJsonObject obj_road = QMap_RoadToJson(GlobalVariable::roadMap);
	WriteToJsonFile(obj_road, "./data/roads.json");
}

void FileIO::ReadMapData()
{
	ReadMapData("./data/points.json", "./data/roads.json");
}

//读取地图数据
void FileIO::ReadMapData(const char* filename_point, const char* filename_road)
{
	QJsonDocument doc_point = ReadJsonFile(filename_point);
	if (doc_point.isObject()) {
		ParseWayPoint(doc_point);;     //读取路径点数据
	}

	QJsonDocument doc_road = ReadJsonFile(filename_road);
	if (doc_road.isObject()) {
		ParseRoad(doc_road);     //读取道路数据
	}
}

void FileIO::ParseWayPointData(QJsonDocument Jdoc)
{
	QJsonObject rootObj = Jdoc.object();
	QJsonValue root = rootObj.value("root");
	if (root.isArray()) {
		QJsonArray points = root.toArray();
		for (int i = 0; i < points.size(); ++i) {
			QJsonValue perPoint = points.at(i);
			if (perPoint.isObject()) {
				QJsonObject perPointObj = perPoint.toObject();

				QJsonValue id = perPointObj.value("id");
				QJsonArray coord = perPointObj.value("coord").toArray();
				QJsonArray roadIds = perPointObj.value("roadIds").toArray();
				QJsonValue type = perPointObj.value("type");
				QJsonValue name = perPointObj.value("name");

				QString Map_name = wayPointMap[i].name;
				uint16_t Map_id = wayPointMap[i].id;
				Coord Map_coord = wayPointMap[i].coord;
				QList<uint16_t> Map_roadIds = wayPointMap[i].roadIds;
				WayPointType Map_type = wayPointMap[i].type;

				Map_name = name.toString();
				Map_id = id.toInt();
				for (int j = 0; j < coord.size(); ++j) {
					Map_coord.x = coord[j].toDouble();
					if (j + 1 == coord.size()) {
						Map_coord.y = coord[j].toDouble();
					}
				}
				Map_type = WayPointType(type.toInt());
				for (int j = 0; j < roadIds.size(); ++j) {
					Map_roadIds[j] = roadIds[j].toInt();
				}
			}
		}
	}
}

void FileIO::ParseWayRoadData(QJsonDocument Jdoc)
{
	QJsonObject obj = Jdoc.object();
	QStringList keys = obj.keys();
	for (int i = 0; i < keys.size(); ++i) {
		QString key = keys.at(i);
		QJsonValue value = obj.value(key);

		if (value.isArray()) {
			qDebug() << "  " << key << ":" << "[";

			QJsonArray Array = value.toArray();

			for (int k = 0; k < Array.size(); ++k)
			{
				qDebug() << "    " << "{";

				QJsonValue subValue = Array.at(k);

				if (subValue.isObject())   //对象
				{
					QJsonObject subObj = subValue.toObject();
					QStringList subkeys = subObj.keys();
					for (int n = 0; n < subkeys.size(); ++n)
					{

						QString subkey = subkeys.at(n);
						QJsonValue thirdValue = subObj.value(subkeys.at(n));

						if (thirdValue.isDouble() && subkey == "id") {               
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							roadMap[k].id = thirdValue.toDouble();         //录入id
						}
						if (thirdValue.isDouble() && subkey == "u") {               
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							roadMap[n].u = thirdValue.toDouble();          //录入u
						}
						if (thirdValue.isDouble() && subkey == "v") {             
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							roadMap[k].v = thirdValue.toDouble();          //录入v
						}
					}
				}
				qDebug() << "    " << "}";
			}
			qDebug() << "  " << "]";
		}
	}
}

//struct WayPoint -> Object
QJsonObject FileIO::WayPointToObject(WayPoint& WayPoint)
{
	QJsonObject obj;
	obj.insert("id", WayPoint.id);
	QByteArray n_a = WayPoint.name.toLocal8Bit();
	QString n = QString::fromLocal8Bit(n_a);
	obj.insert("name", n);

	QJsonArray coordArray;
	coordArray.append(WayPoint.coord.x);
	coordArray.append(WayPoint.coord.y);

	obj.insert("Coord", coordArray);
	obj.insert("type", WayPoint.type);

	QJsonArray roadIdsArray;

	for (uint16_t roadId = 0; roadId < WayPoint.roadIds.size(); ++roadId) {
		roadIdsArray.append(WayPoint.roadIds[roadId]);
	}

	obj.insert("roadIds", roadIdsArray);

	return obj;
}

//struct Road -> Object
QJsonObject FileIO::RoadToObject(Road& road) {
	QJsonObject obj;
	obj.insert("id", road.id);
	obj.insert("u", road.u);
	obj.insert("v", road.v);

	return obj;
}

//point列表转换为Json整体对象
QJsonObject FileIO::QMap_WayPointToJson(QMap<uint16_t, WayPoint>& Map)
{
	QJsonArray array;
	QMap<uint16_t, WayPoint>::iterator itor;
	for (itor = Map.begin(); itor != Map.end(); ++itor) {
		array.append(WayPointToObject(itor.value()));
		//subobj[QString::number(itor.key())] = WayPointToObject(itor.value());
	}
	QJsonObject obj;
	obj.insert("wayPoint", array);
	return obj;
}

//road列表转换为Json整体对象
QJsonObject FileIO::QMap_RoadToJson(QMap<uint16_t, Road>& Map)
{
	QJsonArray array;
	QMap<uint16_t, Road>::iterator itor;
	for (itor = Map.begin(); itor != Map.end(); ++itor) {
		array.append(RoadToObject(itor.value()));
		//subobj[QString::number(itor.key())] = RoadToObject(itor.value());
	}
	QJsonObject obj;
	obj.insert("road", array);
	return obj;
}

//对象写入文件
void FileIO::WriteToJsonFile(QJsonObject& jsonObject, const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		qWarning("Can't open file for writing.");
		return;
	}
	QJsonDocument doc(jsonObject);

	file.write(doc.toJson(QJsonDocument::Indented));
	//qDebug() << doc.toJson(QJsonDocument::Indented);
	//QByteArray jsonData = doc.toJson(QJsonDocument::Indented);
	//file.write(jsonData);

	//file.write(doc.toJson());
}

//读取Json文件
QJsonDocument FileIO::ReadJsonFile(const char* filename)
{
	QFile file(filename);
	file.open(QFile::ReadOnly);

	QByteArray json = file.readAll();
	file.close();

	QJsonDocument doc = QJsonDocument::fromJson(json);

	return doc;
}

//解析路径点
void FileIO::ParseWayPoint(QJsonDocument point) {
	qDebug() << "jsonOfPoint" << ":";
	ParseWayPointData(point);
}

//解析道路
void FileIO::ParseRoad(QJsonDocument road)
{
	qDebug() << "jsonOfRoad" << ":";
	ParseWayRoadData(road);
}
