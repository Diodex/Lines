#include "lines.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Lines w;
	w.show();
	return a.exec();
}


