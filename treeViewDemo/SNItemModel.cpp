#include "SNItemModel.h"
#include <QColor>
#include <QSize>
#include <QFont>
#include <QBrush>

SNItemModel::SNItemModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	m_listTreeItem.clear();
}

SNItemModel::~SNItemModel()
{

}

void SNItemModel::setTreeData(QList<TreeItemStruct> &p_listItemdata)
{
	m_listTreeItem = p_listItemdata;

	beginResetModel();
	endResetModel();

	emit stateChanged(Qt::Unchecked);
}

void SNItemModel::clear()
{
	m_listTreeItem.clear();
	beginResetModel();
	endResetModel();

	emit stateChanged(Qt::Unchecked);
}

void SNItemModel::getSelectedItemData(QMap<unsigned int, void*> &p_mapSelectItem)
{
	p_mapSelectItem.clear();
	for (int i = 0; i < rowCount(); ++i)
	{
		if (m_listTreeItem.at(i).bChecked)
		{
			p_mapSelectItem.insert(m_listTreeItem.at(i).nId, m_listTreeItem.at(i).pUserData);
		}
	}
}

int SNItemModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return m_listTreeItem.count();
}

int SNItemModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant SNItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
		
	int row = index.row();
	int column = index.column();
	TreeItemStruct itemData = m_listTreeItem.at(row);

	switch (role) {
	case Qt::DisplayRole:
		/*if (column == UNIX_TIME_COLUMN)
			return QDateTime::fromTime_t(index_data.unix_time).toString("yyyy-MM-dd hh:mm:ss");
		else if (column == FLASH_ADDR_COLUMN)
			return itemData.addr;*/
		return "";
		break;
	case Qt::CheckStateRole:
		if (column == CHECK_BOX_COLUMN)
			return itemData.bChecked ? Qt::Checked : Qt::Unchecked;
		break;
	case Qt::TextAlignmentRole:
		if (column == CHECK_BOX_COLUMN)
			return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
		else
			return Qt::AlignCenter;
		break;
	case Qt::TextColorRole:
		return QColor(Qt::black);
		break;
	case Qt::SizeHintRole:
		return QSize(100, 30);
		break;
	case Qt::FontRole:
		return QFont("SimSun", 11);
		break;
	default:
		break;
	}

	return QVariant();
}

bool SNItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
	{
		return false;
	}
		
	int column = index.column();
	TreeItemStruct itemData = m_listTreeItem.at(index.row());

	switch (role)
	{
	case Qt::UserRole:		  //根据表头的复选框选择
	case Qt::UserRole + 1:    //根据鼠标点击
		if (column == CHECK_BOX_COLUMN)
		{
			itemData.bChecked = (((Qt::CheckState)value.toInt()) == Qt::Checked);
			m_listTreeItem.replace(index.row(), itemData);

			emit dataChanged(index, index);

			if (role == Qt::UserRole + 1)  //点击鼠标，更新表头复选框状态
			{
				onStateChanged();
			}			

			return true;
		}
		break;
	default:
		return false;
		break;
	}
	return false;
}

Qt::ItemFlags SNItemModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
	{
		return QAbstractItemModel::flags(index);
	}

	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;// | Qt::ItemNeverHasChildren;
	if (index.column() == CHECK_BOX_COLUMN)
	{
		flags |= Qt::ItemIsUserCheckable;
	}
		
	return flags;
}

QModelIndex SNItemModel::index(int row, int column, const QModelIndex &parent) const
{
	if (row < 0 || column < 0 || column >= columnCount(parent))
	{
		return QModelIndex();
	}

	return createIndex(row, column);
}

QModelIndex SNItemModel::parent(const QModelIndex &index) const
{
	Q_UNUSED(index);
	return QModelIndex();
}

QVariant SNItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (section == CHECK_BOX_COLUMN)
		{
			return QString("全选");
		}
		/*else if (section == UNIX_TIME_COLUMN)
		{
			return QString("时间");
		}
		else if (section == FLASH_ADDR_COLUMN)
		{
			return QString("地址");
		}*/
		return "";
		break;
	case Qt::FontRole:
		return QFont("SimSun", 12);
		break;
	case Qt::TextAlignmentRole:
		return Qt::AlignCenter;
		break;
	case Qt::TextColorRole:
		return QColor(Qt::black);
		break;
	case Qt::SizeHintRole:
		return QSize(100, 40);
		break;
	case Qt::BackgroundRole:
		return QBrush(Qt::black);
		break;
	default:
		break;
	}
	return QVariant();
}

void SNItemModel::slot_stateChanged(Qt::CheckState state)
{
	for (int i = 0; i < rowCount(); ++i)
	{
		setData(index(i, CHECK_BOX_COLUMN), state, Qt::UserRole);
	}
}

void SNItemModel::onStateChanged()
{
	int nSelectCount = 0;
	for (int i = 0; i < rowCount(); ++i)
	{
		if (m_listTreeItem.at(i).bChecked)
		{
			++nSelectCount;
		}
	}

	if (0 == nSelectCount)
	{
		emit stateChanged(Qt::Unchecked);
	}
	else if (nSelectCount < rowCount())
	{
		emit stateChanged(Qt::PartiallyChecked);
	}
	else
	{
		emit stateChanged(Qt::Checked);
	}
}