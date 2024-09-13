
#include "FileIO.h"
#include "GlobalVariable.h"
using namespace GlobalVariable;
//写入地图数据
void FileIO::WriteMapData(QMap <uint16_t, WayPoint> pointMap, QMap <uint16_t, Road> roadMap)
{
	QJsonObject obj_point = QMap_WayPointToJson(pointMap);
	QJsonObject obj_road =  QMap_RoadToJson(roadMap);
    //写入waypoint.json文件
	WriteToJsonFile(obj_point, "d://Project2//test_points.json");
	//写入road.json文件
	WriteToJsonFile(obj_road, "d://Project2//test_roads.json");
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
	QJsonObject obj = Jdoc.object();
	QStringList keys = obj.keys();
	
	qDebug() << "{";
	for (int i = 0; i < keys.size(); ++i) 
	{
		QString key = keys.at(i);
		QJsonValue value = obj.value(key);

		if (value.isArray())  //数组
		{
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
							qDebug() << "      "<<subkey << ": " << thirdValue.toDouble();
							wayPointMap[n].id = thirdValue.toDouble();    //录入id
						}
						if (thirdValue.isDouble() && subkey == "WayPointType") {               //浮点
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							//wayPointMap[n].type = thirdValue.toDouble();  //录入type类型
						}

						if (thirdValue.isString()) {               //字符
							qDebug() << "      "<<subkey << ":" << thirdValue.toString();
							wayPointMap[n].name = thirdValue.toString();   //录入name
						}

						if (thirdValue.isArray() && subkey == "coord")  //坐标数组
						{                                       
							QJsonArray finalArray = thirdValue.toArray();
							qDebug() << "      " << subkey << ":" << "[";
							for (int m = 0; m < finalArray.size(); ++m)
							{
								if(m == 0){          //录入x坐标
									wayPointMap[n].coord.x = finalArray[m].toDouble(); 
								}
								if (m == 1) {        //录入y坐标
									wayPointMap[n].coord.y = finalArray[m].toDouble();
								} 

								if (m + 1 == finalArray.size()) {
									qDebug() << "        " << finalArray[m].toDouble() << "]";
								}
								else {
									qDebug() << "        " << finalArray[m].toDouble() << ",";
								}
							}
							
						}

						if (thirdValue.isArray() && subkey == "roadIds")  //路径数组
						{
							QJsonArray finalArray = thirdValue.toArray();
							qDebug() << "      " << subkey << ":" << "[";
							for (int m = 0; m < finalArray.size(); ++m)
							{
								
								wayPointMap[n].roadIds[m] = finalArray[m].toDouble();   //录入路径id

								if (m + 1 == finalArray.size()) {
									qDebug() << "        " << finalArray[m].toDouble() << "]";
								}
								else {
									qDebug() << "        " << finalArray[m].toDouble() << ",";
								}
							}
						}
					}
				}
				qDebug() << "    " << "}";
			}
		qDebug() << "  " << "]";
		}
	}
	qDebug() << "}";
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
							roadMap[n].id = thirdValue.toDouble();         //录入id
						}
						if (thirdValue.isDouble() && subkey == "u") {               
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							roadMap[n].u = thirdValue.toDouble();          //录入u
						}
						if (thirdValue.isDouble() && subkey == "v") {             
							qDebug() << "      " << subkey << ": " << thirdValue.toDouble();
							roadMap[n].v = thirdValue.toDouble();          //录入v
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

	obj.insert("Coord",coordArray);
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
	obj.insert("u",road.u);
	obj.insert("v",road.v);

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

	qDebug() << "jsonOfPoint" <<  ":";
	ParseWayPointData(point);
}

//解析道路
void FileIO::ParseRoad(QJsonDocument road)
{

	qDebug() << "jsonOfRoad" << ":";
	ParseWayRoadData(road);
}

