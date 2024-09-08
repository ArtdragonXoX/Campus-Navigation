
#include "FileIO.h"
#include "GlobalVariable.h"

#include <vector>

//写入地图数据
void FileIO::WriteMapData()
{
	QMap <uint16_t, WayPoint> pointMap;
	WriteWayPointData(pointMap);

	QMap <uint16_t, Road> roadMap;
	WriteRoadData(roadMap);
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
		ParseRoadData(doc_road);     //读取道路数据
	}
}

void FileIO::ParseData(QJsonDocument Jdoc)
{
	QJsonObject obj = Jdoc.object();
	QStringList keys = obj.keys();

	qDebug() << "{";
	for (int i = 0; i < keys.size(); ++i) {

		QString key = keys.at(i);
		QJsonValue value = obj.value(key);

		//对象
		if (value.isObject()) {

			qDebug() << key << ":";

			QJsonObject subObj = value.toObject();
			QStringList subkeys = subObj.keys();

			for (int k = 0; k < subkeys.size(); ++k) {
				QString subkey = subkeys.at(k);
				QJsonValue subValue = subObj.value(subkeys.at(k));

				if (subValue.isDouble()) {      //整型
					qDebug() << subkey << ":" << subValue.toInt();
				}
				if (subValue.isArray()) {       //数组

					QJsonArray array = subValue.toArray();
					for (int n = 0; n < array.count(); n++) {
						QJsonValue thirdValue = array.at(n);

						if (thirdValue.isObject()) {          //对象
							QJsonObject finalObj = thirdValue.toObject();
							QStringList finalkeys = finalObj.keys();
							for (int m = 0; m < finalkeys.size(); ++m) {
								QString finalkey = finalkeys.at(m);
								QJsonValue finalValue = finalObj.value(subkeys.at(m));
								if (finalValue.isDouble()) {
									qDebug() << finalkey << ": " << finalValue.toInt();
								}
							
								if (finalValue.isString()) {
									qDebug() << finalkey << ":" << finalValue.toString();
								}

								if (finalValue.isArray()) {
									QJsonArray finalArray = finalValue.toArray();
									qDebug() << key << ":" << "[";
									for (int m = 0; m < finalArray.size(); ++m)
									{
										if (j + 1 == array.size()) {
											qDebug() << finalArray[m].toInt() << "]";
										}
										else {
											qDebug() << finalArray[m].toInt() << ",";
										}
									}
								
								}
								
							}


						}

				}
			}
		}
	}
	qDebug() << "}";
}


//写入路径点数据
void FileIO::WriteWayPointData(QMap<uint16_t, WayPoint> pointMap)
{
	QMap<uint16_t, WayPoint>::iterator itor;
	for (itor = pointMap.begin(); itor != pointMap.end(); ++itor)
	{
		qDebug() << itor.key() << ":" << itor.value();
	}


}

void FileIO::WriteRoadData(QMap <uint16_t, Road> roadMap)
{
}

//读取json文件
QJsonDocument FileIO::ReadJsonFile(const char* filename)
{
	QFile file(filename);
	file.open(QFile::ReadOnly);
	/*
	if (!file.open(QFile::ReadOnly | QFile::Text)){
		qDebug() << "open error";

	}*/

	QByteArray json = file.readAll();
	file.close();


	QJsonDocument doc = QJsonDocument::fromJson(json);

	/*if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
		qDebug() << "json格式错误" << jsonError.error;
		return;
	}*/

	return doc;

}

//解析路径点数据
void FileIO::ParseWayPoint(QJsonDocument point) {

	qDebug() << "jsonOfPoint" <<  ":";
	ParseData(point);
}

//解析道路数据
void FileIO::ParseRoadData(QJsonDocument road)
{

	qDebug() << "jsonOfRoad" << ":";
	ParseData(road);
}

