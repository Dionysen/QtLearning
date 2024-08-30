#ifndef MYTREEMODEL_H
#define MYTREEMODEL_H

#include "qicon.h"
#include "qobject.h"
#include <QAbstractItemModel>
#include <QIcon>
class MyTreeNode
{
  public:
    MyTreeNode(MyTreeNode* pParent = NULL);

    void addNode(MyTreeNode* pNode);
    void removeNode(int nRow);

    int row();
    int childCount();
    int column();

    MyTreeNode* child(int nRow);
    MyTreeNode* parent();

    bool insertNode(int nRow, MyTreeNode* pNode);

  public:
    struct PersonInfo
    {
      public:
        QString name, job, tel, email, address, Position, id, depart, corporation;
    };

    MyTreeNode*          m_pParent;
    QVector<MyTreeNode*> m_lstChildren;

    QSharedPointer<QIcon> m_Icon;
    PersonInfo            m_Info;
    QString               m_strDeptOrName;
};

class MyTreeModel : public QAbstractItemModel
{
    Q_OBJECT
  public:
    MyTreeModel(QObject* parent = 0);
    ~MyTreeModel();

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

    QModelIndex index(int row, int column, const QModelIndex& parent) const;
    QModelIndex parent(const QModelIndex& child) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex& index, const QVariant& value, int role);

    virtual Qt::ItemFlags flags(const QModelIndex& index) const;

    virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
    virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());

  private:
    void initModel();

  private:
    QSharedPointer<QIcon> m_PersonIcon;
    QSharedPointer<QIcon> m_FolderIcon;

    MyTreeNode* m_pDataSource;
};

#endif  // MYTREEMODEL_H
