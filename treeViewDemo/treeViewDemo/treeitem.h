#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>

//���ڵ�item�����ݽṹ
struct TreeItemStruct
{
//	unsigned int nId;			//ID��ֵ��Ψһ��ʶ��
	QString      strName;		//�ڵ�����
	QString		 strParentCode;	//���ڵ��� 001��001001��001001001......
	QString		 strCode;		//Ψһ��ʶ�����ڵ��� 001��001001��001001001......
	int			 nLevel;		//��ȣ����ڵ�Ϊ0
	bool		 bLeaf;			//�Ƿ�ΪҶ�ӽڵ㣬true:�ǣ�false:��
	int			 nSort;			//����0:������;1:����;2:����
	QString		 strRemark;		//��ע
	bool		 bChecked;		//�Ƿ�ѡ��
	void*		 pUserData;		//�û��Զ��������

	TreeItemStruct()
	{
//		nId = 0;
		strName = "";
		strParentCode = "001";
		strCode = "001";
		nLevel = 0;
		bLeaf = false;
		nSort = 0;
		strRemark = "";
		bChecked = false;
		pUserData = NULL;
	}
};

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
