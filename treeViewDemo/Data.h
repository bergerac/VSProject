#pragma once

//���ڵ�item�����ݽṹ
struct TreeItemStruct
{
	//	unsigned int nId;			//ID��ֵ��Ψһ��ʶ��
	QString      strName;		//�ڵ�����
	QString		 strParentCode;	//���ڵ��� 000��001��001001��001001001......
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