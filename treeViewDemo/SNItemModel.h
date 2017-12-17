#ifndef SNITEMMODEL_H
#define SNITEMMODEL_H

#include <QAbstractItemModel>

#define CHECK_BOX_COLUMN 0

struct TreeItemStruct
{
	unsigned int nId;			//ID��ֵ��Ψһ��ʶ��
	QString      strName;		//�ڵ�����
	unsigned int nParentId;		//���ڵ�ID
	QString		 strCode;		//���� 01��0101��0102
	int			 nLevel;		//��ȣ����ڵ�Ϊ0
	bool		 bLeaf;			//�Ƿ�ΪҶ�ӽڵ㣬true:�ǣ�false:��
	int			 nSort;			//����0:������;1:����;2:����
	QString		 strRemark;		//��ע
	bool		 bChecked;		//�Ƿ�ѡ��
	void*		 pUserData;		//�û��Զ��������

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

	//���ڸ���Model�����Model
	void setTreeData(QList<TreeItemStruct> &p_listItemdata);
	void clear();
	void getSelectedItemData(QMap<unsigned int, void*> &p_mapSelectItem);

	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
	//��ȡrole������
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	//����role������
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	//ʹItem��ʾ��ѡ��
	virtual Qt::ItemFlags flags(const QModelIndex & index) const;

	//���ã�row, column����index
	virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex &index) const;

	//���ر�ͷ��һЩ����
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

signals:
	void stateChanged(Qt::CheckState state);

private slots:
	//�������ͷHeaderView�������źźͲۣ�����Э����ͷ��Item�ĸ�ѡ��״̬
	void slot_stateChanged(Qt::CheckState state);

private:
	void onStateChanged();

private:
	QList<TreeItemStruct> m_listTreeItem;    //Tree�ڵ�����
};

#endif // SNITEMMODEL_H
