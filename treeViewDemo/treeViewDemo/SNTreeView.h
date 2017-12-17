#ifndef SNTREEVIEW_H
#define SNTREEVIEW_H

#include <QTreeView>
#include <QStandardItemModel>

class SNTreeView : public QTreeView
{
	Q_OBJECT

public:
	explicit SNTreeView(QWidget *parent = 0);
	~SNTreeView();

public:
	//初始化树控件样式
	void initStyle();
	//设置是否允许拖动，默认不允许
	void setDropFlag(const bool& p_bFlag = false);
	//设置是否带复选框
	void setCheckable(const bool& p_bCheck = false);
	bool getCheckable();

protected:
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent * event);

	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void startDrag(Qt::DropActions supportedActions);
	void dropEvent(QDropEvent *event);

signals:
	void dragDropend(const QModelIndex& p_objDragIndex, const QModelIndex& p_objDropIndex);
	void treeItemClicked(const QModelIndex& p_objDragIndex, Qt::MouseButton button);

private slots:
	void slot_resizeTreeColumn(const QModelIndex& /*p_pItem*/);

private:
	/******************************模糊搜索*************************************/
	//遍历所有节点，模糊搜索含p_str的item项
	//void searchChild(QStandardItem *p_pItem, const QString &p_str);
	//对搜索到的item项展开其所有子节点
	//void parentExpand(QStandardItem *p_pItem);
	void search(const QString &p_str);

private:
	QModelIndex			m_MousePressItemIndex;
	QStandardItemModel* m_pItemModel;
	bool				m_bCheckable;
	QBrush				m_itemBrush;
};

#endif // SNTREEVIEW_H
