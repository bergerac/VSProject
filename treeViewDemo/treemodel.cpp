/*
    treemodel.cpp

    Provides a simple tree model to show how to create and use hierarchical
    models.
*/

#include "treeitem.h"
#include "treemodel.h"

TreeModel::TreeModel(const QList<TreeItemStruct> &p_treeData, QObject *parent)
    : QAbstractItemModel(parent)
{
	TreeItemStruct rootData;
	rootData.bChecked = false;
	rootData.strName = QStringLiteral("Title");
	rootData.bLeaf = false;
	rootData.strParentCode = "";
    rootItem = new TreeItem(rootData);
	if (NULL != rootItem)
	{
		setupModelData(p_treeData, rootItem);
	}
}

TreeModel::~TreeModel()
{
	if(NULL != rootItem)
	{
		delete rootItem;
		rootItem = NULL;
	}
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
	{
		return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
	}  

    if(NULL != rootItem)
	{
		return rootItem->columnCount();
	}

	return 0;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	{
		return QVariant();
	}

	// 添加图标  
	if (role == Qt::DecorationRole && index.column() == 0)
	{
		return QIcon("images/timg.jpg");
	}
  
	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}
	
	// 显示节点数据值
	TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
	{
		return 0;
	}

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && NULL != rootItem)
	{
		return rootItem->data(section);
	}

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

    TreeItem *parentItem;

    if (!parent.isValid())
	{
		parentItem = rootItem;
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	if(NULL != parentItem)
	{
		TreeItem *childItem = parentItem->child(row);
		if (NULL != childItem)
		{
			return createIndex(row, column, childItem);
		}
	}

	return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
	{
		return QModelIndex();
	}

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (NULL == parentItem || parentItem == rootItem)
	{
		return QModelIndex();
	}

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
	{
		return 0;
	}

    if (!parent.isValid())
	{
		parentItem = rootItem;
	}
    else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	if(NULL != parentItem)
	{
		return parentItem->childCount();
	}
    
	return 0;
}


void TreeModel::setupModelData(const QList<TreeItemStruct> &p_listData, TreeItem *parent)
{
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < p_listData.count())
	{
		QString str = p_listData.at(number).strCode;
        int position = str.length();

		if (position > indentations.last())
		{
			// The last child of the current parent is now the new parent
			// unless the current parent has no children.
			if (parents.last()->childCount() > 0)
			{
				parents << parents.last()->child(parents.last()->childCount() - 1);
				indentations << position;
			}
		}
		else
		{
			while (position < indentations.last() && parents.count() > 0)
			{
				parents.pop_back();
				indentations.pop_back();
			}
		}

		// Append a new item to the current parent's list of children.
		parents.last()->appendChild(new TreeItem(p_listData.at(number), parents.last()));

        ++number;
    }
}

void TreeModel::fuzzySearch(QTreeView* p_tree, const QString &p_str)
{
	if(NULL != rootItem)
	{
		searchChild(p_tree, rootItem, p_str);
	}
}

void TreeModel::searchChild(QTreeView* p_tree, TreeItem *p_pItem, const QString &p_str)
{
	if (NULL == p_pItem || p_str.isEmpty())
	{
		return;
	}

	int childCount = p_pItem->childCount();
	for (int childNo = 0; childNo < childCount; childNo++)
	{
		TreeItem *childItem = p_pItem->child(childNo);
		if (NULL != childItem)
		{
			int nRow = childItem->row();
			QModelIndex childIndex = this->createIndex(nRow, 0, childItem);
			if (childIndex.isValid())
			{
				if ((-1 != childItem->text().indexOf(p_str)) && (!p_tree->isExpanded(childIndex)))
				{
					p_tree->setExpanded(childIndex, true);
					parentExpand(p_tree, childItem);
				}

				searchChild(p_tree, childItem, p_str);
			}
		}
	}
}

void TreeModel::parentExpand(QTreeView* p_tree, TreeItem *p_pItem)
{
	if (NULL == p_pItem || NULL == p_pItem->parentItem())
	{
		return;
	}

	TreeItem *pItem = p_pItem->parentItem();
	int nRow = pItem->row();
	QModelIndex parentIndex = this->createIndex(nRow, 0, pItem);
	if (!p_tree->isExpanded(parentIndex))
	{
		p_tree->setExpanded(parentIndex, true);
	}

	parentExpand(p_tree, pItem);
}