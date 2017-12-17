#pragma once

#include <QtWidgets/QWidget>
#include "ui_treeViewWidget.h"

class treeViewWidget : public QWidget
{
	Q_OBJECT

public:
	treeViewWidget(QWidget *parent = Q_NULLPTR);

private:
	Ui::treeViewWidgetClass ui;
};
