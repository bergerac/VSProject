#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include "Data.h"

class TreeItem
{
public:
    explicit TreeItem(const TreeItemStruct &p_data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *p_pItem);

    TreeItem *child(const int& p_nRow);
    int childCount() const;
    int columnCount() const;
	QVariant data(const int& p_nCol) const;
    int row() const;
    TreeItem *parentItem();
	QString text();

private:
    QList<TreeItem*> m_childItems;  //�ӽڵ㼯��
	TreeItemStruct   m_itemData;    //ÿ����item������		
    TreeItem		 *m_parentItem; //���ڵ�
};

#endif // TREEITEM_H
