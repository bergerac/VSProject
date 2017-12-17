#include "treeViewWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	treeViewWidget w;
	w.show();
	return a.exec();
}
