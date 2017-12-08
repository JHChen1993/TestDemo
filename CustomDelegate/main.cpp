#include "customdelegate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CustomDelegate w;
	w.show();
	return a.exec();
}
