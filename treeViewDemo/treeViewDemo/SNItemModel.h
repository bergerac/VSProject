#ifndef SNITEMMODEL_H
#define SNITEMMODEL_H

#include <QAbstractItemModel>

#define CHECK_BOX_COLUMN 0

struct TreeItemStruct
{
	unsigned int nId;			//ID键值，唯一标识符
	QString      strName;		//节点名称
	unsigned int nParentId;		//父节点ID
	QString		 strCode;		//编码 01、0101、0102
	int			 nLevel;		//深度，根节点为0
	bool		 bLeaf;			//是否为叶子节点，true:是；false:否
	int			 nSort;			//排序，0:不排序;1:升序;2:降序
	QString		 strRemark;		//备注
	bool		 bChecked;		//是否被选中
	void*		 pUserData;		//用户自定义的数据

	TreeItemStruct()
	{
		nId = 0;
		strName = "";
		nParentId = 0;
		strCode = "00";
		nLevel = 0;
		bLeaf = false;
		nSort = 0;
		strRemark = "";
		bChecked = false;
		pUserData = NULL;
	}
};

class SNItemModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit SNItemModel(QObject *parent);
	~SNItemModel();

	//用于更新Model和清空Model
	void setTreeData(QList<TreeItemStruct> &p_listItemdata);
	void clear();
	void getSelectedItemData(QMap<unsigned int, void*> &p_mapSelectItem);

	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
	//获取role的数据
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	//设置role的数据
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	//使Item显示复选框
	virtual Qt::ItemFlags flags(const QModelIndex & index) const;

	//设置（row, column）的index
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &index) const;

	//返回表头的一些数据
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:
	void stateChanged(Qt::CheckState state);

private slots:
	//用于与表头HeaderView交互的信号和槽，可以协调表头和Item的复选框状态
	void slot_stateChanged(Qt::CheckState state);

private:
	void onStateChanged();

private:
	QList<TreeItemStruct> m_listTreeItem;    //Tree节点数据
};

#endif // SNITEMMODEL_H
