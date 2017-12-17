/*
    treeitem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include <QStringList>
#include "treeitem.h"

Q_DECLARE_METATYPE(TreeItemStruct)

TreeItem::TreeItem(const TreeItemStruct &p_data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = p_data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *p_pItem)
{
    m_childItems.append(p_pItem);
}

TreeItem *TreeItem::child(const int& p_nRow)
{
    return m_childItems.value(p_nRow);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data(const int& p_nCol) const
{
	/*QVariant var;
	var.setValue(m_itemData);*/
	return m_itemData.strName;//var;
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (NULL != m_parentItem)
	{
		return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
	}

    return 0;
}

QString TreeItem::text()
{
	return m_itemData.strName;
}