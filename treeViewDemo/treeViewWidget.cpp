#include "treeViewWidget.h"
#include "Data.h"

treeViewWidget::treeViewWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	initForm();
}

treeViewWidget::~treeViewWidget()
{

}

void treeViewWidget::initForm()
{
	QList<TreeItemStruct> listTreeData;
	QString str = "";

	for(int i = 0; i < 10; i++)
	{
		TreeItemStruct treeData;
		treeData.strName = QStringLiteral("¹ã¶«") + QString::number(i);
		treeData.strParentCode = "";
		str += "00" + QString::number(i);
		treeData.strCode = str;
		treeData.nLevel = 0;
		treeData.bLeaf = false;
		treeData.nSort = 0;
		treeData.bChecked = false;
		treeData.pUserData = NULL;

		listTreeData.append(treeData);
	}

	ui.treeView->setTreeModel(listTreeData);
}