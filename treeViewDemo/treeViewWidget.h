#ifndef TREEVIEWWIDGET_H
#define TREEVIEWWIDGET_H

#include <QWidget>
#include "ui_treeViewWidget.h"

class treeViewWidget : public QWidget
{
	Q_OBJECT

public:
	treeViewWidget(QWidget *parent = 0);
	~treeViewWidget();

	void initForm();

private:
	Ui::treeViewWidget ui;
};

#endif // TREEVIEWWIDGET_H
