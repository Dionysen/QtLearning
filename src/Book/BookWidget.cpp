#include "BookWidget.h"
#include "PersonInfo.h"
#include "qabstractitemmodel.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "qtreeview.h"
#include "qwidget.h"
#include "BookTreeList.h"
#include "qwindowdefs.h"
#include <QDialog>

BookWidget::BookWidget(QWidget* parent)
{
    // treeview
    m_TreeView = new QTreeView(this);
    m_TreeView->setModel(new MyTreeModel(m_TreeView));
    m_TreeView->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_TreeView->setHeaderHidden(true);
    m_TreeView->expandAll();
    // btn
    insertBtn = new QPushButton("INSERT", this);
    delBtn    = new QPushButton("DELETE", this);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(insertBtn);
    btnLayout->addWidget(delBtn);

    QVBoxLayout* treeLayout = new QVBoxLayout();
    treeLayout->addWidget(m_TreeView);
    treeLayout->addLayout(btnLayout);

    // person info
    persionInfoWidget = new PersonWidget(this);

    mainLayout = new QHBoxLayout();
    mainLayout->addLayout(treeLayout);
    mainLayout->addWidget(persionInfoWidget);

    setLayout(mainLayout);

    // Connect
    ConnectBtn();
}

void BookWidget::ConnectBtn()
{
    // Connect
    connect(insertBtn, &QPushButton::clicked, this, [=]() {
        QDialog* dia = new QDialog(this);
        dia->show();

        QModelIndex index = m_TreeView->currentIndex();
        if (!index.isValid())
            return;

        if (m_TreeView->model()->insertRow(index.row(), index.parent()))
        {
            // Get index and set index after inserting
            QModelIndex newIndex = m_TreeView->model()->index(index.row(), 0, index.parent());
            m_TreeView->setCurrentIndex(newIndex);
        }
    });

    connect(delBtn, &QPushButton::clicked, this, [=]() {
        QModelIndex index = m_TreeView->currentIndex();
        if (!index.isValid())
            return;
        m_TreeView->model()->removeRow(index.row(), index.parent());
    });

    connect(m_TreeView, &QTreeView::doubleClicked, this, [this](const QModelIndex& index) {
        if (index.isValid())
        {
            QString data = index.data(Qt::DisplayRole).toString();
            emit    OnTreeViewDoubleClicked(data);
        }
    });

    connect(m_TreeView, &QTreeView::clicked, this, [this](const QModelIndex& index) {
        if (index.isValid()) {}
    });
}

BookWidget::~BookWidget()
{
}