#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QTreeView>
#include "Data.h"

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QList<TreeItemStruct> &p_treeData, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	//ģ������
	void fuzzySearch(QTreeView* p_tree, const QString &p_str);
	//����parent��p_pItem��Ӧ
	void searchChild(QTreeView* p_tree, TreeItem *p_pItem, const QString &p_str);
	//����child��p_pItem��Ӧ
	void parentExpand(QTreeView* p_tree, TreeItem *p_pItem);

private:
    void setupModelData(const QList<TreeItemStruct> &p_listData, TreeItem *parent);

    TreeItem *rootItem;
};

#endif // TREEMODEL_H
