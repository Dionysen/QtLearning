#include "BookTreeList.h"
#include "qchar.h"
#include "qicon.h"
#include "qobject.h"
#include <QColor>
#include <QSharedPointer>

MyTreeNode::MyTreeNode(MyTreeNode* pParent)
{
    m_pParent       = pParent;
    m_strDeptOrName = "";
}

void MyTreeNode::addNode(MyTreeNode* pNode)
{
    m_lstChildren.append(pNode);
}

void MyTreeNode::removeNode(int nRow)
{
    if (nRow < 0 || nRow >= m_lstChildren.count())
    {
        return;
    }

    m_lstChildren.remove(nRow);
}

int MyTreeNode::row()
{
    if (NULL == m_pParent)
    {
        return 0;
    }

    return m_pParent->m_lstChildren.indexOf(this);
}

int MyTreeNode::childCount()
{
    return m_lstChildren.count();
}

int MyTreeNode::column()
{
    return 1;
}

MyTreeNode* MyTreeNode::child(int nRow)
{
    if (nRow < 0 || nRow >= m_lstChildren.count())
    {
        return NULL;
    }

    return m_lstChildren.at(nRow);
}

MyTreeNode* MyTreeNode::parent()
{
    return m_pParent;
}

bool MyTreeNode::insertNode(int nRow, MyTreeNode* pNode)
{
    if (nRow < 0 || nRow > m_lstChildren.count())
    {
        return NULL;
    }

    m_lstChildren.insert(nRow, pNode);
    return true;
}


MyTreeModel::MyTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_pDataSource(NULL)
{
    m_PersonIcon = QSharedPointer<QIcon>::create(QString(":/image/person.png"));
    m_FolderIcon = QSharedPointer<QIcon>::create(QString(":/image/folder.png"));

    initModel();
}

MyTreeModel::~MyTreeModel()
{
}

int MyTreeModel::rowCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return 1;

    MyTreeNode* pNode = static_cast<MyTreeNode*>(parent.internalPointer());
    if (pNode)
    {
        return pNode->childCount();
    }

    return 0;
}

int MyTreeModel::columnCount(const QModelIndex& parent) const
{
    if (!parent.isValid())
        return 1;

    MyTreeNode* pNode = static_cast<MyTreeNode*>(parent.internalPointer());
    if (pNode)
    {
        return pNode->column();
    }

    return 0;
}

QModelIndex MyTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!parent.isValid())
    {
        return createIndex(0, column, m_pDataSource);
    }

    MyTreeNode* pParentNode = static_cast<MyTreeNode*>(parent.internalPointer());
    MyTreeNode* pNode       = NULL;
    if (pParentNode)
    {
        pNode = pParentNode->child(row);
    }

    return createIndex(row, column, pNode);
}

QModelIndex MyTreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    MyTreeNode* pChildNode  = static_cast<MyTreeNode*>(child.internalPointer());
    MyTreeNode* pParentNode = m_pDataSource;
    if (pChildNode)
    {
        pParentNode = pChildNode->parent();
    }

    if (pParentNode)
        return createIndex(pParentNode->row(), 0, pParentNode);
    else
        return QModelIndex();
}

QVariant MyTreeModel::data(const QModelIndex& index, int role) const
{
    QVariant varRet;
    if (!index.isValid())
        return varRet;

    MyTreeNode* pNode = static_cast<MyTreeNode*>(index.internalPointer());

    if (NULL == pNode)
        return varRet;

    switch (role)
    {
    case Qt::DisplayRole:
        return QVariant::fromValue(pNode->m_strDeptOrName);
        return varRet;
    case Qt::DecorationRole:  // 使用 DecorationRole 来显示图标
        if (index.column() == 0)
            return *pNode->m_Icon;
        break;
    default:
        break;
    }

    return varRet;
}

bool MyTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    MyTreeNode* pNode = static_cast<MyTreeNode*>(index.internalPointer());
    if (NULL == pNode)
        return false;

    switch (role)
    {
    case Qt::DisplayRole:
        pNode->m_strDeptOrName = value.toString();
    case Qt::DecorationRole:
        *pNode->m_Icon = value.value<QIcon>();
        break;
    default:
        return QAbstractItemModel::setData(index, value, role);
    }

    emit dataChanged(index, index);

    return QAbstractItemModel::setData(index, value, role);
}

Qt::ItemFlags MyTreeModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flag = QAbstractItemModel::flags(index);
    return flag;
}

bool MyTreeModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count);

    MyTreeNode* pParent = m_pDataSource;
    if (parent.isValid())
    {
        pParent = static_cast<MyTreeNode*>(parent.internalPointer());
    }

    for (int i = 0; i < count; ++i)
    {
        MyTreeNode* pNode      = new MyTreeNode(pParent);
        pNode->m_Icon          = m_PersonIcon;
        pNode->m_strDeptOrName = "test";
        pParent->insertNode(row, pNode);
    }
    endInsertRows();

    return true;
}

bool MyTreeModel::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, row, row + count);
    MyTreeNode* pParent = m_pDataSource;
    if (parent.isValid())
    {
        pParent = static_cast<MyTreeNode*>(parent.internalPointer());
    }

    if (pParent)
    {
        for (int i = 0; i < count; ++i)
        {
            pParent->removeNode(row + i);
        }
    }
    endRemoveRows();
    return true;
}


void MyTreeModel::initModel()
{
    m_pDataSource = new MyTreeNode(nullptr);

    m_pDataSource->m_Icon          = m_FolderIcon;
    m_pDataSource->m_strDeptOrName = QString("Department");

    for (int i = 0; i < 10; ++i)
    {
        MyTreeNode* pNode      = new MyTreeNode(m_pDataSource);
        pNode->m_strDeptOrName = QString("Primary%1").arg(i);
        pNode->m_Icon          = m_FolderIcon;
        m_pDataSource->addNode(pNode);

        for (int j = 0; j < 5; ++j)
        {
            MyTreeNode* pNode1      = new MyTreeNode(pNode);
            pNode1->m_strDeptOrName = QString("Primary%1-Secondery%2").arg(i).arg(j);
            pNode1->m_Icon          = m_PersonIcon;
            pNode->addNode(pNode1);
        }
    }
}
