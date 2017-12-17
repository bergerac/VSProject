#pragma once

//树节点item的数据结构
struct TreeItemStruct
{
	//	unsigned int nId;			//ID键值，唯一标识符
	QString      strName;		//节点名称
	QString		 strParentCode;	//父节点编号 000、001、001001、001001001......
	QString		 strCode;		//唯一标识符，节点编号 001、001001、001001001......
	int			 nLevel;		//深度，根节点为0
	bool		 bLeaf;			//是否为叶子节点，true:是；false:否
	int			 nSort;			//排序，0:不排序;1:升序;2:降序
	QString		 strRemark;		//备注
	bool		 bChecked;		//是否被选中
	void*		 pUserData;		//用户自定义的数据

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