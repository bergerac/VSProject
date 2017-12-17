#include "SNTreeView.h"
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>
#include <QHeaderView>

SNTreeView::SNTreeView(QWidget *parent)
	:QTreeView(parent)
	, m_bCheckable(false)
	, m_pItemModel(NULL)
{
	initStyle();
}

SNTreeView::~SNTreeView()
{
}

void SNTreeView::initStyle()
{
	this->setHeaderHidden(true);
	this->setRootIsDecorated(false); //去掉点线
	this->setFocusPolicy(Qt::NoFocus);
	this->setFrameShape(QFrame::Box);
	this->setFrameShadow(QFrame::Plain);
	this->header()->setStretchLastSection(true);
	setStyleSheet("QTreeView {border:none;}");

	connect(this, SIGNAL(expanded(const QModelIndex&)), this, SLOT(slot_resizeTreeColumn(const QModelIndex &)));
}

void SNTreeView::setDropFlag(const bool& p_bFlag)
{
	this->setAcceptDrops(p_bFlag);
}

void SNTreeView::setCheckable(const bool& p_bCheck)
{
	m_bCheckable = p_bCheck;
}

bool SNTreeView::getCheckable()
{
	return m_bCheckable;
}

void SNTreeView::mousePressEvent(QMouseEvent * event)
{
	QTreeView::mousePressEvent(event);

	QPoint pos = event->pos();
	m_MousePressItemIndex = this->indexAt(pos);
}

void SNTreeView::mouseMoveEvent(QMouseEvent * event)
{
	QTreeView::mouseMoveEvent(event);
}

void SNTreeView::mouseReleaseEvent(QMouseEvent * event)
{
	QTreeView::mouseReleaseEvent(event);

	QPoint pos = event->pos();
	QModelIndex objMouseReleaseItemIndex = this->indexAt(pos);
	if (objMouseReleaseItemIndex.isValid())
	{
		Qt::MouseButton button = event->button();
		emit treeItemClicked(objMouseReleaseItemIndex, button);
	}

	//按下和释放要是同一个有效的item
	if (!m_MousePressItemIndex.isValid() || !objMouseReleaseItemIndex.isValid() || (m_MousePressItemIndex != objMouseReleaseItemIndex))
	{
		clearSelection();
		return;
	}
}

void SNTreeView::mouseDoubleClickEvent(QMouseEvent * event)
{
	QPoint point(event->pos());				//获取鼠标点击位置坐标点
	QModelIndex index = indexAt(point);		//取出坐标点处的modelindex

	if (event->button() == Qt::LeftButton)
	{
		if (index.isValid())				//判断index是否是有效的
		{
			QVariant data = index.data(Qt::UserRole + 1);
//			m_loger->Log(NOMAL_LOGLV, "测试", "选中了叶节点%d", data.toInt());
		}
	}
}

void SNTreeView::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/nvr-layoutdata"))
	{
		event->accept();
		this->collapseAll();
	}
	else
	{
		event->ignore();
	}
}

void SNTreeView::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/nvr-layoutdata"))
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void SNTreeView::startDrag(Qt::DropActions supportedActions)
{
	QByteArray itemData;

	QMimeData *mimeData = new QMimeData;
	if(NULL == mimeData)
	{
		return;
	}

	mimeData->setData("application/nvr-layoutdata", itemData);

	QDrag *drag = new QDrag(this);
	if (NULL != drag)
	{
		drag->setMimeData(mimeData);
		drag->exec(supportedActions);
	}

	this->expandAll();
	this->resizeColumnToContents(0);
}

void SNTreeView::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("application/nvr-layoutdata"))
	{
		QPoint pos = event->pos();
		QModelIndex objDropItemIndex = this->indexAt(pos);

		if (objDropItemIndex.isValid())
		{
			emit dragDropend(m_MousePressItemIndex, objDropItemIndex);
		}

	}
	else
	{
		event->ignore();
	}
}

void SNTreeView::slot_resizeTreeColumn(const QModelIndex& /*p_pItem*/)
{
	this->resizeColumnToContents(0);
}

void SNTreeView::search(const QString &p_str)
{
	if(NULL != m_pItemModel)
	{
		m_pItemModel->fuzzySearch(this, p_str);
	}
}

void SNTreeView::setTreeModel(const QList<TreeItemStruct> &p_treeData)
{
	m_pItemModel = new TreeModel(p_treeData, this);
	if (NULL != m_pItemModel)
	{
		this->setModel(m_pItemModel);
	}

	//是否可选
	/*if (getCheckable())
	{

	}
	else
	{

	}*/
//	this->setCheckable(getCheckable());
}

//void SNTreeView::searchChild(QStandardItem *p_pItem, const QString &p_str)
//{
//	if(NULL == m_pItemModel)
//	{
//		return;
//	}
//
//	QModelIndex index = p_pItem->index();
//	if (!index.isValid())
//	{
//		return;
//	}
//
//	int childCount = m_pItemModel->rowCount(index);
//	for (int childNo = 0; childNo < childCount; childNo++)
//	{
//		QModelIndex childIndex = index.child(childNo, 0);
//		if (childIndex.isValid())
//		{
//			QStandardItem *childItem = m_pItemModel->itemFromIndex(childIndex);
//			if (NULL != childItem)
//			{
//				if ( (-1 != childItem->text().indexOf(p_str)) && (!this->isExpanded(childIndex)) )
//				{
//					this->setExpanded(childIndex, true);
//					childItem->setBackground(QBrush(Qt::green));
//					parentExpand(childItem);
//				}
//				else
//				{
//					childItem->setBackground(QBrush(m_itemBrush));
//				}
//
//				searchChild(childItem, p_str);
//			}
//		}
//	}
//}
//
//void SNTreeView::parentExpand(QStandardItem *p_pItem)
//{
//	if(NULL == p_pItem || NULL == p_pItem->parent())
//	{
//		return;
//	}
//	
//	QStandardItem *pItem = p_pItem->parent();
//	QModelIndex index = pItem->index();
//	if (!this->isExpanded(index))
//	{
//		this->setExpanded(index, true);
//	}
//
//	parentExpand(pItem);
//}