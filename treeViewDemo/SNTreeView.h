#ifndef SNTREEVIEW_H
#define SNTREEVIEW_H

#include <QTreeView>
#include "treemodel.h"
#include "Data.h"

class SNTreeView : public QTreeView
{
	Q_OBJECT

public:
	explicit SNTreeView(QWidget *parent = 0);
	~SNTreeView();

public:
	//��ʼ�����ؼ���ʽ
	void initStyle();
	//�����Ƿ������϶���Ĭ�ϲ�����
	void setDropFlag(const bool& p_bFlag = false);
	//�����Ƿ����ѡ��
	void setCheckable(const bool& p_bCheck = false);
	bool getCheckable();
	void setTreeModel(const QList<TreeItemStruct> &p_treeData);

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
	/******************************ģ������*************************************/
	//�������нڵ㣬ģ��������p_str��item��
	//void searchChild(QStandardItem *p_pItem, const QString &p_str);
	//����������item��չ���������ӽڵ�
	//void parentExpand(QStandardItem *p_pItem);
	void search(const QString &p_str);

private:
	QModelIndex			m_MousePressItemIndex;
	TreeModel*			m_pItemModel;
	bool				m_bCheckable;
};

#endif // SNTREEVIEW_H
