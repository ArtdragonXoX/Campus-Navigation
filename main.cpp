#include "MianWindow.h"
#include <QtWidgets/QApplication>

#include "Definition.h"
using namespace std;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MianWindow w;
	w.show();
	return a.exec();
}
